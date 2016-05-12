SUBDIRS = UniquePtr SharedPtr Checklist

subdirs:
		for dir in $(SUBDIRS); do \
			$(MAKE) -C $$dir; \
		done
