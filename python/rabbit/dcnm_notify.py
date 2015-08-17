#!/usr/bin/env python 
import pika
import sys  
import requests,json

class Cdnmrest:
    def __init__ (self,ip='172.27.252.69',user='admin',pwd='cisco12',\
            proto='http', certVerify='False'):
        print "here"
        self.ip = ip
        self.auth = (user,pwd)
        self.headers =  None
        self.baseUrl = proto + '://' + ip
        self.token = None
        self.verify = certVerify
        
    def logon(self,expiry=300000):
        url = self.baseUrl + "/rest/logon"
        payload = {}
        payload["expirationTime"] = expiry
        r = requests.post(url, data=json.dumps(payload), headers=self.headers,\
                auth=self.auth, verify=self.verify)
        print 'O', r.status_code, r.text, '\n'
        print r.json()["Dcnm-Token"]
        print url
        print self.headers
        print self.auth
        print self.verify
        token = r.json()["Dcnm-Token"]
        self.headers = {'sessionId': self.token}
        if r and (r.status_code >= 200):
              session_id = r.json().get('Dcnm-Token')
        self.headers.update({'Dcnm-Token': session_id })
        print r.text
        print self.headers
        print session_id
        return r

    def listorg(self):
#        url = self.baseUrl + "/rest/poap/servers/server-name"
#        payload = {}
#        payload["expirationTime"] = 1000
#        r = requests.get(url, headers=self.headers)
#        print url
#        print r
        url = self.baseUrl + "/fmrest/config/templates"
        r = requests.get(url, headers=self.headers)
        print url
        print r
#        print r.text
#        url = self.baseUrl + "/fmrest/config/templates"
        return r



credentials = pika.PlainCredentials('admin', 'cisco123')
parameters = pika.ConnectionParameters(host = '172.27.252.70',
                                       port = 5672,
                                      credentials=credentials
                                       )

#connection = pika.BlockingConnection(pika.ConnectionParameters(
#        host='172.27.252.70'))
connection = pika.BlockingConnection(parameters)
channel = connection.channel()

#channel.exchange_declare(exchange='DCNMExchange',
#                         type='topic')

result = channel.queue_declare(exclusive=True)
queue_name = result.method.queue

binding_keys = sys.argv[1:]
if not binding_keys:
    print >> sys.stderr, "Usage: %s [binding_key]..." % (sys.argv[0],)
    sys.exit(1)

for binding_key in binding_keys:
    channel.queue_bind(exchange='DCNMExchange',
                       queue=queue_name,
                       routing_key=binding_key)

channel.queue_bind(exchange='DCNMExchange',
                  queue=queue_name,
                  routing_key="success.cisco.dcnm.event.auto-config.organization.create")
print ' [*] Waiting for logs. To exit press CTRL+C'

def dcnm_callback(ch, method, properties, body):
    print " [x] %r:%r" % (method.routing_key, body,)

channel.basic_consume(dcnm_callback,
                      queue=queue_name,
                      no_ack=True)



channel.start_consuming()


x = Cdnmrest('172.27.252.70','admin','cisco123','http', 'False')
x.logon(30000)
x.listorg()



