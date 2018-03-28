# This script makes a dummy localization file with (many) entries for performance checks.

num_of_entries = 3 # 10000

with open("TE_long.lang.txt", "w") as f:
    f.write("UTF8\nTE_long\n")
    for i in range(num_of_entries):
        f.write("TEST_" + str(i) + "_ID : \" test long " + str(i) + "\";\n")
