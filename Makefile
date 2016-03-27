SUBDIRS = UniquePtr SharedPtr

subdirs:
		for dir in $(SUBDIRS); do \
			$(MAKE) -C $$dir; \
		done
