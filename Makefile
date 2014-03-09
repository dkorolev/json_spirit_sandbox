# Prerequisites:
# sudo apt-get install libjson-spirit-dev

CPP=g++
CPP11=${CPP} -std=c++11
CPPFLAGS+= -DBOOST_NO_RVALUE_REFERENCES

all: test

test: json.txt binary
	cat $< | ./binary

binary: test.cc
	${CPP11} ${CPPFLAGS} -o $@ $<

clean:
	rm -rf binary
