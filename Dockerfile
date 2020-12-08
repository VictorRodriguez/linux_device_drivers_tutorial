FROM centos:latest

RUN yum -y groupinstall "Development Tools"
RUN yum -y install ncurses-devel \
	hmaccalc \
	zlib-devel \
	binutils-devel \
	elfutils-libelf-devel \
	bc \
	openssl-devel
COPY scripts/build-kernel.sh /

RUN mkdir /devel/
COPY Makefile /devel/
COPY src/ /devel/src

CMD  cd /devel/ && make

#CMD  /build-kernel.sh
