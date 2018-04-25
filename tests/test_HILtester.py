from HILtester import HIL

# -------------
# tests section
# -------------

def test_parse_input():
    """
    Tester for parse_input function
    """
    assert HIL.parse_input(["3d", "05", "21", "40"]) == "=\x05!@"
    assert HIL.parse_input(["3d", "05", "21", "40"]) == "\x3d\x05\x21\x40"
    assert HIL.parse_input(["ff", "ff", "ff", "00"]) == "\xff\xff\xff\x00"
    assert HIL.parse_input(["ac", "01", "00", "fe"]) == "\xac\x01\x00\xfe"
    assert HIL.parse_input(["00", "00", "00", "ff"]) == "\x00\x00\x00\xff"

def test_parse_output():
    """
    Tester for parse_output function
    """

    data1 = ["3d", "05", "21", "40"]
    data2 = ["ff", "ff", "ff", "00"]
    data3 = ["ac", "01", "00", "fe"]
    data4 = ["00", "00", "00", "ff"]

    assert HIL.parse_output(''.join(x.decode('hex') for x in data1)) == data1
    assert HIL.parse_output(''.join(x.decode('hex') for x in data2)) == data2
    assert HIL.parse_output(''.join(x.decode('hex') for x in data3)) == data3
    assert HIL.parse_output(''.join(x.decode('hex') for x in data4)) == data4

# ----------
# main tests
# ----------

# test_parse_input()
# test_parse_output()

h1 = HIL(port = 'COM9')
h1()
# h1.compare()
