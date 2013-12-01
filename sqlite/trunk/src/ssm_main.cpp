#include "w_defines.h"
#include "sm_vas.h"

static ss_m *ssm = 0;

struct file_info_t {
    static const char* key;
    stid_t             fid;
    rid_t              first_rid;
    int                num_rec;
    int                rec_size;
};
const char* file_info_t::key = "SCANFILE";

ostream &
operator << (ostream &o, const file_info_t &info)
{
    o << "key " << info.key
    << " fid " << info.fid
    << " first_rid " << info.first_rid
    << " num_rec " << info.num_rec
    << " rec_size " << info.rec_size ;
    return o;
}

class smthread_driver_t: public smthread_t {
	int _argc;
	char **_argv;

protected:
	const char * _progType;
	const char *_device_name;
	smsize_t _quota;
	int _num_rec;
	smsize_t _rec_size;
	lvid_t _lvid;
	vid_t _vid;
	rid_t _start_rid;
	stid_t _fid;
	bool _initialize_device;
	option_group_t* _options;
	int _retval;

	virtual w_rc_t do_work();
	virtual void start_ssm();
public:

	smthread_driver_t(int argc, char **argv) :
		smthread_t(t_regular, "smthread_driver_t"), _argc(argc), _argv(argv),
				_progType("server"), _device_name(NULL), _quota(0),
				_num_rec(0), _rec_size(0), _vid(1), _initialize_device(false),
				_options(NULL), _retval(0) {
	}

	virtual ~smthread_driver_t() {
		if (_options)
			delete _options;
	}

	virtual void run();
	void statistics() const;
	int return_value() const {
		return _retval;
	}
	const char * get_device_name() const {
		return _device_name;
	}
	bool is_init_device() const {
		return _initialize_device;
	}

	w_rc_t handle_options();
	w_rc_t do_init();
	w_rc_t find_file_info();
	w_rc_t create_the_file();
	w_rc_t scan_the_file();
	w_rc_t scan_the_root_index();
	w_rc_t no_init();
	w_rc_t init_config_options(option_group_t& options);

};

void smthread_driver_t::statistics() const {
	sm_stats_info_t stats;
	W_COERCE(ss_m::gather_stats(stats));
	cout << " SM Statistics : " << endl << stats << endl;
}

w_rc_t smthread_driver_t::find_file_info() {
	file_info_t info;

	W_DO(ssm->begin_xct());

	stid_t root_iid;
	W_DO(ss_m::vol_root_index(_vid, root_iid));

	const vec_t key_vec_tmp(file_info_t::key, strlen(file_info_t::key));

	smsize_t info_len = sizeof(info);

	bool found;
	W_DO(ss_m::find_assoc(root_iid,
					key_vec_tmp,
					&info, info_len, found));
	if (!found) {
		cerr << "No file information found" << endl;
		return RC(fcASSERT);
	} else {
		cout << "Found assoc " << file_info_t::key << " --> " << info << endl;

		_fid = info.fid;
		_start_rid = info.first_rid;
		_rec_size = info.rec_size;
		_num_rec = info.num_rec;
	}

	W_DO(ssm->commit_xct());

	return RCOK;
}

rc_t smthread_driver_t::create_the_file() {
	file_info_t info;

	W_DO(ssm->begin_xct());

	W_DO(ssm->create_file(_vid, _fid, smlevel_3::t_regular));
	info.fid = _fid;

	W_DO(ssm->commit_xct());

	return RCOK;
}

rc_t smthread_driver_t::scan_the_root_index() {
	W_DO(ssm->begin_xct());
	stid_t _root_iid;
	W_DO(ss_m::vol_root_index(_vid, _root_iid));
	cout << "Scanning index " << _root_iid << endl;
	scan_index_i scan(_root_iid, scan_index_i::ge, vec_t::neg_inf,
			scan_index_i::le, vec_t::pos_inf, false, ss_m::t_cc_kvl);
	bool eof(false);
	int i(0);
	smsize_t klen(0);
	smsize_t elen(0);
#define MAXKEYSIZE 100
	char keybuf[MAXKEYSIZE];
	file_info_t info;

	do {
		w_rc_t rc = scan.next(eof);
		if (rc.is_error()) {
			cerr << "Error getting next: " << rc << endl;
			_retval = rc.err_num();
			return rc;
		}
		if (eof)
			break;

		W_DO(scan.curr(NULL, klen, NULL, elen));
		vec_t key(&keybuf[0], klen);
		vec_t elem(&info, elen);
		W_DO(scan.curr(&key, klen, &elem, elen));
		keybuf[klen] = '\0';
		cout << "Key " << (const char *) keybuf << endl;
		cout << "Value " << " { fid " << info.fid << " first_rid "
				<< info.first_rid << " #rec " << info.num_rec << " rec size "
				<< info.rec_size << " }" << endl;
		i++;
	} while (!eof);
	W_DO(ssm->commit_xct());
	return RCOK;
}

rc_t smthread_driver_t::scan_the_file() {
	cout << "Scanning file " << _fid << endl;
	W_DO(ssm->begin_xct());

	scan_file_i scan(_fid);
	pin_i* cursor(NULL);
	bool eof(false);
	int i(0);

	do {
		w_rc_t rc = scan.next(cursor, 0, eof);
		if (rc.is_error()) {
			cerr << "Error getting next: " << rc << endl;
			_retval = rc.err_num();
			return rc;
		}
		if (eof)
			break;

		cout << "Record " << i << " Rid " << cursor->rid();
		vec_t header(cursor->hdr(), cursor->hdr_size());
		int hdrcontents;
		header.copy_to(&hdrcontents, sizeof(hdrcontents));
		cout << " Hdr {" << hdrcontents << "}";

		const char *body = cursor->body();
		w_assert0(cursor->body_size() == _rec_size);
		cout << " Body {" << body << "}";
		cout << endl;
		i++;
	} while (!eof);w_assert1(i == _num_rec);

	W_DO(ssm->commit_xct());
	return RCOK;
}

rc_t smthread_driver_t::do_init() {
	cout << "-i: Initialize " << endl;

	{
		devid_t devid;
		cout << "Formatting device: " << _device_name << " with a " << _quota
				<< "KB quota ..." << endl;
		W_DO(ssm->format_dev(_device_name, _quota, true));

		cout << "Mounting device: " << _device_name << endl;
		// mount the new device
		u_int vol_cnt;
		W_DO(ssm->mount_dev(_device_name, vol_cnt, devid));

		cout << "Mounted device: " << _device_name << " volume count "
				<< vol_cnt << " device " << devid << endl;

		// generate a volume ID for the new volume we are about to
		// create on the device
		cout << "Generating new lvid: " << endl;
		W_DO(ssm->generate_new_lvid(_lvid));
		cout << "Generated lvid " << _lvid << endl;

		// create the new volume
		cout << "Creating a new volume on the device" << endl;
		cout << "    with a " << _quota << "KB quota ..." << endl;

		W_DO(ssm->create_vol(_device_name, _lvid, _quota, false, _vid));
		cout << "    with local handle(phys volid) " << _vid << endl;

	}

	W_DO(create_the_file());
	_initialize_device = true;

	return RCOK;
}

rc_t smthread_driver_t::no_init() {
	cout << "Using already-existing device: " << _device_name << endl;
	// mount already existing device
	devid_t devid;
	u_int vol_cnt;
	w_rc_t rc = ssm->mount_dev(_device_name, vol_cnt, devid);
	if (rc.is_error()) {
		cerr << "Error: could not mount device: " << _device_name << endl;
		cerr << "   Did you forget to run the server with -i?" << endl;
		return rc;
	}

	// find ID of the volume on the device
	lvid_t* lvid_list;
	u_int lvid_cnt;
	W_DO(ssm->list_volumes(_device_name, lvid_list, lvid_cnt));
	if (lvid_cnt == 0) {
		cerr << "Error, device has no volumes" << endl;
		exit(1);
	}
	_lvid = lvid_list[0];
	delete[] lvid_list;

	W_DO(find_file_info());
	W_DO(scan_the_root_index());
	W_DO(scan_the_file());

	return RCOK;
}

void smthread_driver_t::start_ssm() {
	cout << "Starting SSM and performing recovery ..." << endl;
	ssm = new ss_m();
}

w_rc_t smthread_driver_t::init_config_options(option_group_t& options) {
	w_rc_t rc;

	char* prog_name = strrchr(_argv[0], '/');
	if (prog_name == NULL) {
		prog_name = _argv[0];
	} else {
		prog_name += 1; /* skip the '/' */
		if (prog_name[0] == '\0') {
			prog_name = _argv[0];
		}
	}

	W_DO(options.add_class_level("sqlite"));
	W_DO(options.add_class_level(_progType));
	W_DO(options.add_class_level(prog_name));

	// read the config file to set options
	{
		w_ostrstream err_stream;
		const char* opt_file = "SHORECONFIG";
		option_file_scan_t opt_scan(opt_file, &options);

		rc
				= opt_scan.scan(true /*override*/, err_stream, true /*option names must be complete and correct*/);
		if (rc.is_error()) {
			cerr << "Error in reading option file: " << opt_file << endl;
			cerr << "\t" << err_stream.c_str() << endl;
			return rc;
		}
	}

	// check required options for values
	{
		w_ostrstream err_stream;
		rc = options.check_required(&err_stream);
		if (rc.is_error()) {
			cerr << "These required options are not set:" << endl;
			cerr << err_stream.c_str() << endl;
			return rc;
		}
	}

	return RCOK;
}

w_rc_t smthread_driver_t::handle_options() {
	const int option_level_cnt = 3;

	_options = new option_group_t(option_level_cnt);
	if (!_options) {
		cerr << "Out of memory: could not allocate from heap." << endl;
		_retval = 1;
		return RC(fcINTERNAL);
	}
	option_group_t &options(*_options);

	option_t* opt_device_name = 0;
	W_DO(options.add_option(
					"device_name",
					"device/file name",
					NULL,
					"device containing volume holding file to scan",
					true,
					option_t::set_value_charstr,
					opt_device_name
			));

	option_t* opt_device_quota = 0;
	W_DO(options.add_option(
					"device_quota",
					"# > 1000",
					"2000",
					"quota for device",
					false,
					option_t::set_value_long,
					opt_device_quota
			));

	option_t* opt_num_rec = 0;
	W_DO(options.add_option(
					"num_rec",
					"# > 0",
					"100",
					"number of records in file",
					true,
					option_t::set_value_long,
					opt_num_rec
			));

	W_DO(ss_m::setup_options(&options));

	w_rc_t rc = init_config_options(options);
	if (rc.is_error()) {
		_retval = 1;
		return rc;
	}

	_device_name = opt_device_name->value();
	_quota = strtol(opt_device_quota->value(), 0, 0);
	_num_rec = strtol(opt_num_rec->value(), 0, 0);

	return RCOK;
}

void smthread_driver_t::run() {
	w_rc_t rc = handle_options();
	if (rc.is_error()) {
		_retval = 1;
		return;
	}

	start_ssm();
	if (!ssm) {
		cerr << "Error: Out of memory for ss_m" << endl;
		_retval = 1;
		return;
	}

	sm_config_info_t config_info;
	rc = ss_m::config_info(config_info);
	if (rc.is_error()) {
		cerr << "Could not get storage manager configuration info: " << rc
				<< endl;
		_retval = 1;
		return;
	}
	_rec_size = config_info.max_small_rec;
	_rec_size += config_info.small_rec_overhead;
	_rec_size /= 2;
	_rec_size -= config_info.small_rec_overhead;

	rc = do_work(); // do_work() is defined in shell.cpp as it is closely related to shell
	if (rc.is_error()) {
		cerr << "Failure: " << rc << endl;
		_retval = 1;
	}

	cout << "\nShutting down SSM ..." << endl;
	delete ssm;
	cout << "Finished!" << endl;

	return;
}
