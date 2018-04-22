import serial
from time import sleep


class HIL(object):
    """
    This class provides Hardware-In-Loop tests capabilities for Bamocar Control Board, 
    for development, testing and debugging of Bamocar Engine Controler by AGH Racing Electric Team
    """

    def __init__(self, port='COM3', wait=1):
        """
        Opens up specified port for communication with board, loads test data from file.
        wait - how long to take before reading serial port
        """
        try:
            self.ser = serial.Serial(port, baudrate=115200, timeout=1, parity=serial.PARITY_NONE)
            self.inFile = open("dataIN.txt", "r")
            self.outFile = open("dataOUT.txt", "w+")
            self.refFile = open("dataREF.txt", "r")
            self.wait = wait
        except serial.SerialException as e:
            print "Some trouble with serial port: " + str(e)
        except IOError as e:
            print "There's no 'dataIN.txt' or 'dataREF.txt' file!"

    def __del__(self):
        """
        Clean up method, closes serial port and files and deletes its instances
        """
        self.ser.close()
        self.inFile.close()
        self.outFile.close()
        self.refFile.close()
        del self.ser

    def __call__(self):
        """
        Caller, run tests by sending data from input file and saving data to output file
        """
        for line in self.inFile:
            self.ser.write(self.parse_input(line.split()[:-1]))
            sleep(self.wait)
            s = self.parse_output(self.ser.read(int(line.split()[-1])))
            s = str(' '.join(s)) + '\n'
            self.outFile.write(s)
        else:
            self.outFile.flush()

    def compare(self):
        """
        Method for automatic comparing expected and recevied output from board
        """
        self.outFile.seek(0, 0)
        try:
            for line in self.outFile:
                ref = self.refFile.readline()
                assert line == ref
            else:
                print "Everything's fine, tests passed"
        except AssertionError:
            print "TEST FAILED!\nShould be " + ref.strip('\n') + " but "+ line.strip('\n') + " received."

    @staticmethod
    def parse_input(data):
        """
        This method takes list of string with hex data to send via serial port
        """
        data = bytes(r'\x' + r'\x'.join(data))  # 'bytes' for Python 3 compability, in Python 2 does nothing
        return eval("'%s'" % data)

    @staticmethod
    def parse_output(data):
        """
        This method provides easy and efficient way to read data from serial port
        """
        res = ' '.join(x.encode('hex') for x in data)
        return res.split()
