import unittest
import in3


class In3ClientTest(unittest.TestCase):

    def setUp(self):
        self.in3client = in3.Client()

    def test_configure(self):
        client = in3.Client()
        self.assertIsNotNone(client)
        client = in3.Client(in3.model.ClientConfig())
        self.assertIsNotNone(client)
        # client = in3.Client(in3.ClientConfig(**in3.model.MAINNET.__dict__))
        # self.assertIsNotNone(client)
        client = in3.Client('mainnet')
        self.assertIsNotNone(client)

    def test_node_list(self):
        nl = self.in3client.node_list()
        self.assertIsInstance(nl, in3.model.NodeList)

    def test_abi_encode(self):
        params = "(address,string)", "0x1234567890123456789012345678901234567890", "xyz"
        encoded = self.in3client.abi_encode(*params)
        expected = "0xdd06c847000000000000000000000000123456789012345678901234567890123456789000000000000000000000" + \
                   "0000000000000000000000000000000000000000004000000000000000000000000000000000000000000000000000" + \
                   "0000000000000378797a0000000000000000000000000000000000000000000000000000000000"
        self.assertEqual(encoded, expected)
        params = "getData(address,string,uint8,string)", "0x1234567890123456789012345678901234567890", \
                 "xyz", "0xff", "abc"
        expected = "0x597574130000000000000000000000001234567890123456789012345678901234567890000000000000000000000" + \
                   "00000000000000000000000000000000000000000800000000000000000000000000000000000000000000000000000" + \
                   "0000000000ff00000000000000000000000000000000000000000000000000000000000000c00000000000000000000" + \
                   "00000000000000000000000000000000000000000000378797a00000000000000000000000000000000000000000000" + \
                   "00000000000000000000000000000000000000000000000000000000000000000000000000000361626300000000000" + \
                   "00000000000000000000000000000000000000000000000"
        encoded = self.in3client.abi_encode(*params)
        self.assertEqual(encoded, expected)
        err0 = "address,string,uint8,string", "0x1234567890123456789012345678901234567890", "xyz", "0xff", "abc"
        err1 = "()", "0x1234567890123456789012345678901234567890"
        err2 = "(test)", "0x1234567890123456789012345678901234567890"
        with self.assertRaises(AssertionError):
            self.in3client.abi_encode(*err0)
        with self.assertRaises(AssertionError):
            self.in3client.abi_encode(*err1)
        with self.assertRaises(AssertionError):
            self.in3client.abi_encode(*err2)

    def test_abi_decode(self):
        err0 = "address,string,uint8,string", "0x0000000000000000000000001234567890123456789012345678901234567"
        err1 = "()", "0x0000000000000000000000001234567890123456789012345678901234567"
        err2 = "(test)", "0x0000000000000000000000001234567890123456789012345678901234567"
        err3 = "(address,uint256)", "0000000000000000000000001234567890123456789012345678901234567"
        with self.assertRaises(AssertionError):
            self.in3client.abi_decode(*err0)
        with self.assertRaises(AssertionError):
            self.in3client.abi_decode(*err1)
        with self.assertRaises(AssertionError):
            self.in3client.abi_decode(*err2)
        with self.assertRaises(AssertionError):
            self.in3client.abi_decode(*err3)
        params = "(address,uint256)", "0x0000000000000000000000001234567890123456789012345678901234567890000000000" + \
                 "0000000000000000000000000000000000000000000000000000005"
        expected = ['0x1234567890123456789012345678901234567890', '0x05']
        decoded = self.in3client.abi_decode(*params)
        self.assertEqual(decoded, expected)
        params = "(address,string,uint8,string)", \
                 "0x00000000000000000000000012345678901234567890123456789012345678900000000000000000000000000000000" + \
                 "00000000000000000000000000000008000000000000000000000000000000000000000000000000000000000000000" + \
                 "ff00000000000000000000000000000000000000000000000000000000000000c000000000000000000000000000000" + \
                 "0000000000000000000000000000000000378797a000000000000000000000000000000000000000000000000000000" + \
                 "00000000000000000000000000000000000000000000000000000000000000000003616263000000000000000000000" + \
                 "0000000000000000000000000000000000000"
        expected = ["0x1234567890123456789012345678901234567890", "xyz", "0xff", "abc"]
        decoded = self.in3client.abi_decode(*params)
        self.assertEqual(decoded, expected)


class In3ClientKovanTest(In3ClientTest):

    def setUp(self):
        self.in3client = in3.Client('kovan')

    def test_configure(self):
        client = in3.Client('kovan')
        self.assertIsNotNone(client)
        # client = in3.Client(str(in3.model.Chain.KOVAN))
        # self.assertIsNotNone(client)


class In3ClientGoerliTest(In3ClientTest):

    def setUp(self):
        self.in3client = in3.Client('goerli')

    def test_configure(self):
        client = in3.Client('goerli')
        self.assertIsNotNone(client)
        # client = in3.Client(str(in3.model.Chain.GOERLI))
        # self.assertIsNotNone(client)


if __name__ == '__main__':
    unittest.main()