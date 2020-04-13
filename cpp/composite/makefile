DIRECTORIES = file \
	   		  directory \
	   		  tree \
	   		  
.PHONY: debug_%
debug_%:
	cd ./$* && make 

.PHONY: release_%
release_%:
	cd ./$* && make release
         
.PHONY: test_%       
test_%:
	cd ./$* && make test

.PHONY: all
all:
	for dir in $(DIRECTORIES); do \
		make debug_$$dir &&\
		make release_$$dir &&\
		make test_$$dir;\
	done

.PHONY: clean_%
clean_%:
	cd ./$* && make clean
