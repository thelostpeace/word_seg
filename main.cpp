#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TSocket.h>

#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <iostream>

#include "factory.h"
#include "WordSegService.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::concurrency;
using ::apache::thrift::server::TThreadPoolServer;
using namespace ::WordSeg;
using boost::shared_ptr;

class WordSegServiceHandler : virtual public WordSegServiceIf {
public:
    WordSegServiceHandler() {}

    void pre_process() {
        // 正常可能会有一些预处理
    }

    void post_process() {
        // 正常肯定会有后处理策略，模型不可能做到100%正确的
    }

    void word_segment(WordSegResponse &_return, const WordSegRequest &req) {
        pre_process();

        Model *model = ModelMaker::getInstance()->makeModel("CRF");
        word_seg_t segs;
        model->predict(req.query, segs);
        _return.tokens = segs.tokens;
        _return.begin_idx = segs.begin_idx;
        _return.end_idx = segs.end_idx;
        
        post_process();
    }
};

int main(int argc, char **argv) {
    int port = 19292;
    int thread_num = 32;

    Model *model = ModelMaker::getInstance()->makeModel("CRF");
    if (model == NULL) {
        std::cerr << "model create failed!!!" << std::endl;
        return -2;
    }
    if (0 != model->loadModel(CRF_MODEL_FILE)) {
        std::cerr << "crf model load failed!!!" << std::endl;
        return -3;
    }

    shared_ptr<WordSegServiceHandler> handler(new WordSegServiceHandler());
    shared_ptr<TProcessor> processor(new WordSegServiceProcessor(handler));
    shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
    shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(thread_num);
    shared_ptr<PosixThreadFactory> threadFactory = shared_ptr<PosixThreadFactory>(new PosixThreadFactory());
    threadManager->threadFactory(threadFactory);
    threadManager->start();

    TThreadPoolServer server(processor, serverTransport, transportFactory, protocolFactory, threadManager);

    try {
        server.serve();
    } catch (const TException &e) {
        std::cerr << "thrift exception: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
