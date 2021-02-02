SUB_DIRS := implementation

all:

%:
	@for DIR in $(SUB_DIRS); do \
		$(MAKE) -C $${DIR} $@ || exit 1; \
	done;
