from flask import Flask
from flask import request
import json
import sys

app = Flask(__name__)

#policies 


@app.route("/policies", methods=['POST'])
def add_policy():

    print "Request to add policy:\n"
    msg = json.loads(request.data)
    print json.dumps(msg)
    return "Hello"

@app.route("/policies/<policyId>", methods=['GET'])
def get_policy(policyId):
    print "Request to get policy "+ str(policyId)    
    return "Hello World!"

@app.route("/policies/<policyId>", methods=['DELETE'])
def delete_policy(policyId):
    print "Request to delete policy "+ str(policyId)
    return "Hello World!"

# services 

@app.route("/services", methods=['POST'])
def add_service():

    print "Request to add service:\n"
    msg = json.loads(request.data)
    print json.dumps(msg)
    return "Service Hello"

@app.route("/services/<serviceId>", methods=['GET'])
def get_service(serviceId):
    print "Request to get service "+ str(serviceId)    
    return "Service Hello World!"

@app.route("/services/<serviceId>", methods=['DELETE'])
def delete_service(serviceId):
    print "Request to delete policy "+ str(policyId)
    return "Service world!"


if __name__ == "__main__":
    address = 'localhost'
    port = 9090
    if (len(sys.argv) > 2):
        address = sys.argv[1]
        port = int(sys.argv[2])
    app.run(host=address, port=port)
    
    

