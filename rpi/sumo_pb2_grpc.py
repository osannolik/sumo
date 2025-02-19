# Generated by the gRPC Python protocol compiler plugin. DO NOT EDIT!
import grpc

import sumo_pb2 as sumo__pb2


class SumoProtocolStub(object):
  # missing associated documentation comment in .proto file
  pass

  def __init__(self, channel):
    """Constructor.

    Args:
      channel: A grpc.Channel.
    """
    self.SumoIO = channel.stream_stream(
        '/sumoprotocol.SumoProtocol/SumoIO',
        request_serializer=sumo__pb2.MotorCommand.SerializeToString,
        response_deserializer=sumo__pb2.Sensors.FromString,
        )


class SumoProtocolServicer(object):
  # missing associated documentation comment in .proto file
  pass

  def SumoIO(self, request_iterator, context):
    """A Bidirectional streaming RPC:
    Accepts a stream of MotorCommand sent while a route is being traversed,
    while receiving other MotorCommand (e.g. from other users).
    """
    context.set_code(grpc.StatusCode.UNIMPLEMENTED)
    context.set_details('Method not implemented!')
    raise NotImplementedError('Method not implemented!')


def add_SumoProtocolServicer_to_server(servicer, server):
  rpc_method_handlers = {
      'SumoIO': grpc.stream_stream_rpc_method_handler(
          servicer.SumoIO,
          request_deserializer=sumo__pb2.MotorCommand.FromString,
          response_serializer=sumo__pb2.Sensors.SerializeToString,
      ),
  }
  generic_handler = grpc.method_handlers_generic_handler(
      'sumoprotocol.SumoProtocol', rpc_method_handlers)
  server.add_generic_rpc_handlers((generic_handler,))
