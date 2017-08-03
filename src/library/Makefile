default:
	gcc -shared -Wall -o libStageArm.so -fPIC stagearm.c
install:
	make install`(uname -s)`
.PHONY: installLinux
installLinux:
	if [ -d "/usr/lib64" ]; then cp libStageArm.so /usr/lib64/; else cp libStageArm.so /usr/lib/; fi
	if [ -d "/usr/lib64" ]; then cp libStageArm.so /lib64/; else cp libStageArm.so /lib/; fi
		cp stageArm.h /usr/include/

.PHONY: installDarwin
installDarwin:
	cp libStageArm.so /usr/local/lib/
	cp stageArm.h /usr/local/include/
uninstall:
	make uninstall`(uname -s)`
.PHONY: uninstallLinux
uninstallLinux:
	if [ -d "/usr/lib64" ]; then rm /usr/lib64/libStageArm.so; else rm /usr/lib/libStageArm.so; fi
	rm /usr/include/stageArm.h
.PHONY: uninstallDarwin
uninstallDarwin:
	rm /usr/local/lib/stageArm.dylib
	rm /usr/local/include/stageArm.h
