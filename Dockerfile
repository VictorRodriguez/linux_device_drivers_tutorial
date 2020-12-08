FROM centos:latest

RUN yum -y groupinstall "Development Tools"
RUN yum -y install ncurses-devel \
	hmaccalc \
	zlib-devel \
	binutils-devel \
	elfutils-libelf-devel \
	bc \
	openssl-devel

