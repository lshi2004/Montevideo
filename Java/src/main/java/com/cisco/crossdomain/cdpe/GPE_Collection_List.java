package com.cisco.crossdomain.cdpe;

import java.util.ArrayList;
import java.util.List;

public class GPE_Collection_List {
	    private List<GPE_Collection_Interface> GPE_list;
	    
	    
	    GPE_Collection_List () {	    	
	    	GPE_list = new ArrayList<GPE_Collection_Interface>();
	    	GPE_list.add(new Policies(null));  	
	    	GPE_list.add(new Group());
	    	GPE_list.add(new End_points());
	    	GPE_list.add(new Controllers());
	    	GPE_list.add(new Services());
	    	GPE_list.add(new Actions());
	    	GPE_list.add(new Classifiers());
	    	GPE_list.add(new Rule_sets());
	    	GPE_list.add(new Categories());
	    	GPE_list.add(new Tenants());
	    }
	    
	    public GPE_Collection_Interface find(String relative_uri){
	    	for (int i = 0; i < GPE_list.size(); i++) {
				if (relative_uri.contains(GPE_list.get(i).getCommonName())) {
					return this.GPE_list.get(i);
		    	}
			}
			return null;
	    }
	    
		public int size() {
			return this.GPE_list.size();
		}
}
