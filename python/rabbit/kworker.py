#!/usr/bin/env python 

from kombu.mixins import ConsumerMixin
from kombu.log import get_logger
from kombu import Queue, Exchange


logger = get_logger(__name__)


class Worker(ConsumerMixin):
    task_queue = Queue('notifications.info', Exchange('neutron', 'topic'))

    def __init__(self, connection):
        self.connection = connection

    def get_consumers(self, Consumer, channel):
        return [Consumer(queues=[self.task_queue],
                         accept=['json'],
                         callbacks=[self.process_task])]

    def process_task(self, body, message):
        print("RECEIVED MESSAGE: %r" % (body, ))
        message.ack()

if __name__ == '__main__':
    from kombu import Connection
    from kombu.utils.debug import setup_logging
    # setup root logger
    setup_logging(loglevel='DEBUG', loggers=[''])

    with Connection('amqp://admin:cisco123@172.27.252.70:5672//') as conn:
        try:
            print(conn)
            worker = Worker(conn)
            worker.run()
        except KeyboardInterrupt:
            print('bye bye')


