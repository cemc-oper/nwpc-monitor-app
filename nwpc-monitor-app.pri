source_base_dir = $$PWD

sub_dir = $$_PRO_FILE_PWD_
sub_dir ~= s,^$$re_escape($$PWD),,
build_base_dir = $$clean_path($$OUT_PWD)
build_base_dir ~= s,$$re_escape($$sub_dir)$,,
