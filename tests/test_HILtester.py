from HILtester import HIL

# -------------
# tests section
# -------------

data_in1 = ["3d", "05", "21", "40"]
data_in2 = ["ff", "ff", "ff", "00"]
data_in3 = ["ac", "01", "00", "fe"]
data_in4 = ["00", "00", "00", "ff"]

data_out1 = b"\x3d\x05\x21\x40"
data_out2 = b"\xff\xff\xff\x00"
data_out3 = b"\xac\x01\x00\xfe"
data_out4 = b"\x00\x00\x00\xff"

def test_parse_input():
    """
    Tester for parse_input function
    """
    assert HIL.parse_input(data_in1) == data_out1
    assert HIL.parse_input(data_in2) == data_out2
    assert HIL.parse_input(data_in3) == data_out3
    assert HIL.parse_input(data_in4) == data_out4

def test_parse_output():
    """
    Tester for parse_output function
    """
    assert HIL.parse_output(data_out1) == data_in1
    assert HIL.parse_output(data_out2) == data_in2
    assert HIL.parse_output(data_out3) == data_in3
    assert HIL.parse_output(data_out4) == data_in4

# ----------
# main tests
# ----------

# test_parse_input()
# test_parse_output()

h1 = HIL()
h1()
# h1.compare()
