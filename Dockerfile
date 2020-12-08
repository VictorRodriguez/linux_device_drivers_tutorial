FROM centos:latest

RUN yum -y groupinstall "Development Tools"
RUN yum -y install ncurses-devel \
	hmaccalc \
	zlib-devel \
	binutils-devel \
	elfutils-libelf-devel \
	bc \
	openssl-devel \
	kernel-devel \
	kernel-headers

COPY scripts/build-kernel.sh /
CMD  /build-kernel.sh
# copy from linux/ the generated uimage to your mount volume
