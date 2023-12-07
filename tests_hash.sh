#!/bin/bash

run_test() {
    echo "-------------------------------------------------------------------------------------------------------------------------------------------------"
    echo -e "Test: $1"

    output=$(eval $1)
    echo -e "$output"

    if [ "$output" = "$2" ]; then
        echo -e "\033[32mTest Success\033[0m"
    else
        echo -e "\033[31mTest Failed\033[0m"
        echo "Expected: $2"
    fi
}

hash_by_openssl() {
    local command="$1"
    output=$(bash -c "$command")
    echo -e "\033[30mHash by OpenSSL:"
    echo -e "$output\033[0m"
}

# Tests MD5
echo "---------------------------------------------------------------------------------------------------------------------------------------------------"
echo -e "-                                                                \033[36mSUBJECT TESTS\033[0m                                                                    -"
echo "And above all," > file
echo "watch with glittering eyes, this is a big file, and need at least 2 chunks" > long_file
run_test 'echo "42 is nice" | ./ft_ssl md5' '(stdin)= 35f1d6de0302e2086a4e472266efb3a9'
run_test 'echo "42 is nice" | ./ft_ssl md5 -p' '("42 is nice")= 35f1d6de0302e2086a4e472266efb3a9'
run_test 'echo "Pity the living." | ./ft_ssl md5 -q -r' 'e20c3b973f63482a778f3fd1869b7f25'
run_test './ft_ssl md5 file' 'MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'
run_test './ft_ssl md5 -r file' '53d53ea94217b259c11a5a2d104ec58a file'
run_test './ft_ssl md5 -s "pity those that aren'"'"'t following baerista on spotify."' 'MD5 ("pity those that aren'"'"'t following baerista on spotify.") = a3c990a1964705d9bf0e602f44572f5f'
run_test 'echo "be sure to handle edge cases carefully" | ./ft_ssl md5 -p file' '("be sure to handle edge cases carefully")= 3553dc7dc5963b583c056d1b9fa3349c
MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'
run_test 'echo "some of this will not make sense at first" | ./ft_ssl md5 file' 'MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'
run_test 'echo "but eventually you will understand" | ./ft_ssl md5 -p -r file' '("but eventually you will understand")= dcdd84e0f635694d2a943fa8d3905281
53d53ea94217b259c11a5a2d104ec58a file'
run_test 'echo "GL HF let'"'"'s go" | ./ft_ssl md5 -p -s "foo" file' '("GL HF let'"'"'s go")= d1e3cc342b6da09480b27ec57ff243e2
MD5 ("foo") = acbd18db4cc2f85cedef654fccc4a4d8
MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'
run_test 'echo "one more thing" | ./ft_ssl md5 -r -p -s "foo" file -s "bar"' '("one more thing")= a0bd1876c6f011dd50fae52827f445f5
acbd18db4cc2f85cedef654fccc4a4d8 "foo"
53d53ea94217b259c11a5a2d104ec58a file
ft_ssl: md5: -s: No such file or directory
ft_ssl: md5: bar: No such file or directory'
run_test 'echo "just to be extra clear" | ./ft_ssl md5 -r -q -p -s "foo" file' 'just to be extra clear
3ba35f1ea0d170cb3b9a752e3360286c
acbd18db4cc2f85cedef654fccc4a4d8
53d53ea94217b259c11a5a2d104ec58a'
run_test 'echo "" | ./ft_ssl md5 -r -q' '68b329da9893e34099c7d8ad5cb9c940'
run_test './ft_ssl md5 long_file' 'MD5 (long_file) = 299f4552f22c85e81c13972fa0faca06'

echo "-------------------------------------------------------------------------------------------------------------------------------------------------"
echo -e "-                                                           \033[36mEND OF SUBJECT TESTS\033[0m                                                                -"
echo "-------------------------------------------------------------------------------------------------------------------------------------------------"
echo
echo "-------------------------------------------------------------------------------------------------------------------------------------------------"
echo -e "-                                                               \033[36mSHA256 TESTS\033[0m                                                                    -"

run_test 'echo "42 is nice" | ./ft_ssl sha256' '(stdin)= a5482539287a4069ebd3eb45a13a47b1968316c442a7e69bc6b9c100b101d65d'
hash_by_openssl 'echo "42 is nice" | openssl sha256 -r | awk "{print \$1}"'

run_test 'echo "42 is nice" | ./ft_ssl sha256 -p' '("42 is nice")= a5482539287a4069ebd3eb45a13a47b1968316c442a7e69bc6b9c100b101d65d'
hash_by_openssl 'echo "42 is nice" | openssl sha256 -r | awk "{print \$1}"'

run_test 'echo "Pity the living." | ./ft_ssl sha256 -q -r' '40133cfe543247c1cae0ffb0003c1179ce9fb0046bee19f9fca167380643ba45'
hash_by_openssl 'echo "Pity the living." | openssl sha256 -r | awk "{print \$1}"'

run_test 'echo "" | ./ft_ssl sha256 -r -q' '01ba4719c80b6fe911b091a7c05124b64eeece964e09c058ef8f9805daca546b'
hash_by_openssl 'echo "" | openssl sha256 -r | awk "{print \$1}"'

run_test './ft_ssl sha256 -r -q long_file' '3114bd95992e8215d20e129544202982a5a6ada6138dd5a5095cb38310de52e1'
hash_by_openssl 'openssl sha256 -r long_file | awk "{print \$1}"'

echo "-------------------------------------------------------------------------------------------------------------------------------------------------"
echo -e "-                                                           \033[36mEND OF SHA256 TESTS\033[0m                                                                 -"
echo "-------------------------------------------------------------------------------------------------------------------------------------------------"
echo
echo "-------------------------------------------------------------------------------------------------------------------------------------------------"
echo -e "-                                                             \033[36mWHIRLPOOL TESTS\033[0m                                                                   -"

run_test 'echo "42 is nice" | ./ft_ssl whirlpool' '(stdin)= f2e4e782ee1994d5210f4a4982785817b31d11762e531ded3f29dc1caef1878f14fad7cf668149993776b769d07b23e4969ebac3edbd0cd2567afaa6dd11d4ec'
hash_by_openssl 'echo "42 is nice" | openssl whirlpool -r -provider legacy | awk "{print \$1}"'

run_test 'echo "42 is nice" | ./ft_ssl whirlpool -p' '("42 is nice")= f2e4e782ee1994d5210f4a4982785817b31d11762e531ded3f29dc1caef1878f14fad7cf668149993776b769d07b23e4969ebac3edbd0cd2567afaa6dd11d4ec'
hash_by_openssl 'echo "42 is nice" | openssl whirlpool -r -provider legacy | awk "{print \$1}"'

run_test 'echo "Pity the living." | ./ft_ssl whirlpool -q -r' 'c420c6f8ec9c9558a842b89625547d860f3ac277803c190bc635f0c82f1d807a252b0d936982faad9d37ef4cbc59760445fc0cd3271543c1ff3e5a7d59b31a69'
hash_by_openssl 'echo "Pity the living." | openssl whirlpool -r -provider legacy | awk "{print \$1}"'

run_test 'echo "" | ./ft_ssl whirlpool -r -q' '898126aab982feb2e4b99fee1e4b1cfb4208c76f35945119d24de8744016b56666dabeed478e3a9a36032bc9b8da05db7e79156dc76a7447ad0d39067745de1e'
hash_by_openssl 'echo "" | openssl whirlpool -r -provider legacy | awk "{print \$1}"'

run_test './ft_ssl whirlpool -r -q long_file' 'e21821d55489b464cc64847bae109af6719f04a338f422de50208420408da324950541ef5380a33967bd332135f6f2d798705d442d93c922331609b1e64f742e'
hash_by_openssl 'openssl dgst -whirlpool -r -provider legacy long_file | awk "{print \$1}"'

echo "-------------------------------------------------------------------------------------------------------------------------------------------------"
echo -e "-                                                          \033[36mEND OF WHIRLPOOL TESTS\033[0m                                                               -"
echo "-------------------------------------------------------------------------------------------------------------------------------------------------"

# Clean up
rm file
rm long_file
