//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


  int system_init_for_mytest()
  {
      int result = 0;
      int important_data_type = 12;
      int start_time = 14;
      message_t msg;
      ip_address_t controller_addr;
      
      memset(&msg, 0, sizeof(msg));
      init_ip_address(controller_addr, 127, 1, 0 ,0);
      msg.id = 1;
      msg.type = CONFIG;
      msg.types.confuguration.age = 44
      msg.types.confuguration.dictionary = DEFAULT;
      msg.types.confuguration.modifier = NONE;
      msg.types.confuguration.name = "A";

      result = system_init(
                          &msg,
                          important_data_type,
                          start_time,
                          &controller_addr); 

      return result;
  }