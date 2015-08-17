package com.cisco.crossdomain.cdpe;

import io.vertx.core.json.JsonObject;

class DCInfo
{
	public String dcId ;
	public String address ;
	public int    port ;
    public String policyId ;

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((address == null) ? 0 : address.hashCode());
		result = prime * result + ((dcId == null) ? 0 : dcId.hashCode());
		result = prime * result + port;
		return result;
	}
	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		DCInfo other = (DCInfo) obj;
		if (address == null) {
			if (other.address != null)
				return false;
		} else if (!address.equals(other.address))
			return false;
		if (dcId == null) {
			if (other.dcId != null)
				return false;
		} else if (!dcId.equals(other.dcId))
			return false;
		if (port != other.port)
			return false;
		return true;
	}
	public String getDcId() {
		return dcId;
	}
	public void setDcId(String dcId) {
		this.dcId = dcId;
	}
	public String getAddress() {
		return address;
	}
	public void setAddress(String address) {
		this.address = address;
	}
	public int getPort() {
		return port;
	}
	public void setPort(int port) {
		this.port = port;
	}
	public DCInfo(JsonObject jsonMessage)
	{
		this(jsonMessage.getString("dcId"), jsonMessage.getString("address"), jsonMessage.getInteger("port"), jsonMessage.getString("policyId")) ;
	}
	public DCInfo(String dcId, String address, int port, String policyId)
	{
		this.dcId = dcId ;
		this.address = address ;
		this.port = port ;
	        this.policyId = policyId;
	}
	
}
