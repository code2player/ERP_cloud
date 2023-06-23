SUBDIRS = login register user stationer admin benchmark_test

all:
	@for subdir in $(SUBDIRS); do        $(MAKE) -C $$subdir;              done
	cp -f register/register_server bin
	cp -f login/login_server bin
	cp -f user/user_server bin
	cp -f stationer/stationer_server bin
	cp -f admin/admin_server bin

.PHONY:clean
clean:
	@for subdir in $(SUBDIRS); do        $(MAKE) -C $$subdir clean;        done
	rm -f bin/*