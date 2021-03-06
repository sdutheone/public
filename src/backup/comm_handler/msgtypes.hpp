
/* msgtypes.hpp
 * author: Jinliang Wei
 * */

#ifndef __PETUUM_MSGTYPES_HPP__
#define __PETUUM_MSGTYPES_HPP__

/**
 * General Message format
 *
 * 1. EMsgType
 * 2. Type specific information
 *
 * This format relies on 0mq's multi-part message.
 */

namespace petuum {

  const int IP_ADDR_STR_LEN_MAX = 16;
  const int PORT_STR_LEN_MAX = 6;
  // CommXXXs are only internal message types. More specifically, these are the
  // message types that are seen by comm thread and app threads. Those types
  // are only seen within the CommHandler.
  // When a message is sent out to via the router socket to another process, the
  //  message types are RouterXXXs, while CommXXXs are removed
  enum EMsgType {CommConnect, CommPubInit, CommSubInit, CommPubInitSend,
                 CommShutDown, CommSend, CommPublish, CommThrReg, CommThrDereg, 
		 CommThrSend, CommThrKeyReg, CommThrKeyDereg, CommThrKeySend,
		 RouterConnect, RouterMsg, RouterPubInit, RouterPubInitReply,
                 RouterThrMsg, RouterThrKeyMsg};

  struct CommConnectMsg{
    EMsgType type_;
    int32_t cid_;
    char ip_[IP_ADDR_STR_LEN_MAX];
    char port_[PORT_STR_LEN_MAX];

    CommConnectMsg():
      type_(CommConnect){}
  };

  struct CommPubInitMsg{
    EMsgType type_;
    char ip_[IP_ADDR_STR_LEN_MAX];
    char port_[PORT_STR_LEN_MAX];

    CommPubInitMsg():
      type_(CommPubInit){}
  };


  struct CommSubInitMsg{
    EMsgType type_;
    char ip_[IP_ADDR_STR_LEN_MAX];
    char port_[PORT_STR_LEN_MAX];
    int32_t num_gids_;

    CommSubInitMsg():
      type_(CommSubInit){}
  };

  struct CommPubInitSendMsg{
    EMsgType type_;
    int32_t gid_;

    CommPubInitSendMsg():
      type_(CommPubInitSend){}
  };

  struct CommSendMsg{
    EMsgType type_;
    int32_t cid_;

    CommSendMsg():
      type_(CommSend){}
  };

  struct CommPublishMsg{
    EMsgType type_;
    int32_t gid_; // publish group id

    CommPublishMsg():
      type_(CommPublish){}
  };

  struct CommThrRegMsg {
    EMsgType type_;
    pthread_t thrid_;

    CommThrRegMsg():
      type_(CommThrReg){}
  };

  struct CommThrDeregMsg{
    EMsgType type_;
    pthread_t thrid_;
    
    CommThrDeregMsg():
      type_(CommThrDereg){}
  };

  struct CommThrSendMsg{
    EMsgType type_;
    int32_t cid_; // destination client id
    pthread_t thrid_; // destination thread id

    CommThrSendMsg():
      type_(CommThrSend){}
  };

  struct CommThrKeyRegMsg{
    EMsgType type_;
    pthread_t thrid_;
    int32_t key_;
    
    CommThrKeyRegMsg():
      type_(CommThrKeyReg){}
  };

  struct CommThrKeyDeregMsg{
    EMsgType type_;
    pthread_t thrid_;
    int32_t key_;
    
    CommThrKeyDeregMsg():
      type_(CommThrKeyDereg){}
  };

  struct CommThrKeySendMsg{
    EMsgType type_;
    int32_t cid_; // destination client id
    pthread_t thrid_; // destination thread id
    int32_t key_;

    CommThrKeySendMsg():
      type_(CommThrKeySend){}
  };

  struct RouterThrMsgMsg{
    EMsgType type_;
    pthread_t thrid_;

    RouterThrMsgMsg():
      type_(RouterThrMsg){}
  };

  struct RouterThrKeyMsgMsg{
    EMsgType type_;
    pthread_t thrid_;
    int32_t key_;

    RouterThrKeyMsgMsg():
      type_(RouterThrKeyMsg){}
  };

  /*
   * Specific Message Format
   * 
   * Internal messages:
   * 1. CommConnect
   * 1) destination client id
   * 2) destination IP
   * 3) destination port
   *
   * 2. CommPubInit
   * 1) publish IP*
   * 2) publish port*
   *
   * 3. CommSubInit
   * 1) publish IP
   * 2) publish port
   * 3) number of gids (N)
   * 4) N gids each a one message part
   *
   * 4. CommPubInitSend
   * 1) publish group id
   *
   * 5. CommPublish
   * 1) group id
   * 2) msg data
   *
   * 6. CommSend
   * 1) client id
   * 2) msg data
   *
   * 7. CommShutDown
   * nothing
   *
   * 8. CommThrReg
   * 1) thread id
   *
   * 9. CommThrDereg
   * 1) thread id
   *
   * 10. CommThrSend
   * 1) client id
   * 2) thread id
   * 3) msg data
   *
   * External messages:
   *
   * 1. RouterConnect
   * nothing
   *
   * 2. RouterMsg
   * msg data
   *
   * 3. RouterPubInit
   * publisher id
   *
   * 4. RouterPubReply
   *  nothing
   *
   * 5. RouterThrMsg
   *
   * */

}

#endif /* DISKSTREAM_MSGTYPES_HPP_ */
