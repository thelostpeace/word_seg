#!/usr/bin/env python
# -*- coding: utf-8 -*- 

import sys
sys.path.append('./gen-py')
import json

from WordSeg import WordSegService
from WordSeg.ttypes import * 

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

try:
    transport = TSocket.TSocket('localhost', 12019)
    transport = TTransport.TBufferedTransport(transport)
    protocol = TBinaryProtocol.TBinaryProtocol(transport)
    client = WordSegService.Client(protocol)

    transport.open()

    while True:
        request = WordSegRequest()
        request.query_id = "123456"
        #request.query = "等下班了，我要坐398路公交车去五道口地铁站。"
        request.query = raw_input(">>> (type EXIT to quit) ")
        if request.query == "EXIT":
            break
        response = client.word_segment(request)
        print ">>> %s" % json.dumps(response.tokens, ensure_ascii=False)
except Thrift.TException, e:
    print '%s' % e.message
