include (../../nwpc-monitor-app.pri)

TEMPLATE=aux

build_python_vendor_dir = $${build_vendor_dir}/python
build_python_vendor_dir~=s,/,\\,g
python_dir = $${python_env_dir}
python_dir~=s,/,\\,g

QMAKE_POST_LINK += $$quote(IF NOT EXIST $${build_python_vendor_dir} ( MKDIR $${build_python_vendor_dir} & XCOPY $${python_dir} $${build_python_vendor_dir} /E /Y)$$escape_expand(\n\t))
