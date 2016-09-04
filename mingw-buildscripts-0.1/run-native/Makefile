TARGET=x86_64-w64-mingw32
TARGETS=x86_64-w64-mingw32 i686-w64-mingw32

all: native-func-$(TARGET).dll run-native-$(TARGET).exe subdirs

subdirs:
	$(MAKE) -C native-func TARGET=$(TARGET)

clean:
	rm -f *.o *.a *.dll
	$(MAKE) -C native-func TARGET=$(TARGET) clean


native-func-stub-$(TARGET).o: native-func-stub.c
	$(TARGET)-gcc -municode -o "$@" -g -c -DBUILDING_NATIVE_FUNC_DLL "$<"

libnative-func-$(TARGET).a \
native-func-$(TARGET).dll:native-func-stub-$(TARGET).o
	$(TARGET)-gcc -shared -o "$@" \
	"$<" -Wl,--out-implib,libnative-func-$(TARGET).a

run-native-$(TARGET).exe: run-native-$(TARGET).o libnative-func-$(TARGET).a
	$(TARGET)-gcc -municode -mconsole -g -o "$@" -L. run-native-$(TARGET).o -lnative-func-$(TARGET)

run-native-$(TARGET).o: run-native.c
	$(TARGET)-gcc -municode -mconsole -g -c -o "$@" "$<"


check:
	for target in $(TARGETS) ; \
	do \
		$(MAKE) TARGET="$$target" all && \
		echo $$target ; \
		cp ./run-native-$$target.exe uname.exe && \
		$$target env WINEDLLPATH=. ./uname.exe -a || exit ; \
		echo $$target ; \
	done
	$(MAKE) -C native-func check
