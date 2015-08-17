import os,subprocess
import uuid

def populate_db(obj_arr, collectionName):
    #Delete the collection
    curl_str = """curl -X DELETE --data-binary @- --dump - http://localhost:8529/_db/cdpe/_api/collection/"""+collectionName+""" <<EOF
{"name":\""""+collectionName+"""\"}
EOF"""
    curl_op = os.system(curl_str)
    
    #Create the collection
    curl_str = """curl -X POST --data-binary @- --dump - http://localhost:8529/_db/cdpe/_api/collection <<EOF
{"name":\""""+collectionName+"""\"}
EOF"""
    curl_op = os.system(curl_str)
    
    for i in range(0,len(obj_arr)):
        curl_str = """curl -H "Content-Type: application/json" -X POST -d '"""+obj_arr[i]+"""' http://localhost:8529/_db/cdpe/_api/document?collection="""+collectionName
        os.system(curl_str)
    return
    
if __name__ == "__main__":
    ep_arr = [
             '{"_key":\"'+str(uuid.uuid4())+'\", "name": "10.0.35.1/24"}',
             '{"_key":\"'+str(uuid.uuid4())+'\", "name": "10.0.36.1/24"}',
             '{"_key":\"'+str(uuid.uuid4())+'\", "name": "10.4.28.1/24"}',
             '{"_key":\"'+str(uuid.uuid4())+'\", "name": "10.4.30.1/24"}',
             '{"_key":\"'+str(uuid.uuid4())+'\", "name": "10.20.101.1/24"}',
             '{"_key":\"'+str(uuid.uuid4())+'\", "name": "10.20.102.1/24"}',
             '{"_key":\"'+str(uuid.uuid4())+'\", "name": "10.20.102.2/24"}',
             '{"_key":\"'+str(uuid.uuid4())+'\", "name": "10.30.0.1/24"}',
             '{"_key":\"'+str(uuid.uuid4())+'\", "name": "10.30.0.2/24"}',
             '{"_key":\"'+str(uuid.uuid4())+'\", "name": "10.30.0.3/24"}'
         ]
    #populate the End-point collection
    populate_db(ep_arr,"ep")
    
    categories_arr = [
             '{"_key":\"'+str(uuid.uuid4())+'\","name": "Backup and Storage"}',
             '{"_key":\"'+str(uuid.uuid4())+'\","name": "Business and Productivity "}',
             '{"_key":\"'+str(uuid.uuid4())+'\","name": "Database"}',
             '{"_key":\"'+str(uuid.uuid4())+'\","name": "Internet Security"}',
             '{"_key":\"'+str(uuid.uuid4())+'\","name": "Email"}',
             '{"_key":\"'+str(uuid.uuid4())+'\","name": "Software Updates"}',
             '{"_key":\"'+str(uuid.uuid4())+'\","name": "Voice & Video"}'
         ]
    #populate the categories
    populate_db(categories_arr,"categories")
    
    
    Num_of_Tenants = 2
    tenants_arr = [None]* Num_of_Tenants

    for i in range(0,Num_of_Tenants):
        unique_id_str = str(uuid.uuid4())
        tenant_name = "Mock_Tenant_"+str(i+1)
        
        tenants_arr[i] = '{"_key":"'+unique_id_str+'","name": "'+tenant_name+'","id":"'+unique_id_str+'"}'
    
    #populate the Tenants collection
    populate_db(tenants_arr,"tenants")
