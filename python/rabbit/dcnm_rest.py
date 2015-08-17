import requests,json
#from xml.etree import ElementTree

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


x = Cdnmrest('172.27.252.69','admin','cisco123','http', 'False')
x.logon(30000)
x.listorg()



