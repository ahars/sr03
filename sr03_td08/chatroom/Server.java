// Java  chatroom/Server.java
package chatroom;

public class Server { 

	public static void main(String args[]) { 

		java.util.Properties props = System.getProperties();
		props.put("org.omg.CORBA.ORBClass", "com.ooc.OBServer.ORB");
		props.put("org.omg.CORBA.ORBSingletonClass", "com.ooc.CORBA.ORBSingleton");

		int status = 0;
		org.omg.CORBA.ORB orb = null;

		try {
			orb = org.omg.CORBA.ORB.init(args, props);
			status = run(orb);
		} catch (Exception ex) {
			ex.printStackTrace();
			status = 1;
		}

		if (orb != null) {

			try {
				orb.destroy();
			} catch (Exception ex) {
				ex.printStackTrace();
				status = 1;
			}
		}
		System.exit(status);
	}

	//----- run() -----
	static int run(org.omg.CORBA.ORB orb) throws org.omg.CORBA.UserException {

   		org.omg.CORBA.Object objRef = null;
	   	org.omg.CosNaming.NamingContext ncRef = null;

   		try {

		   	objRef = orb.resolve_initial_references("NameService");
			ncRef = org.omg.CosNaming.NamingContextHelper.narrow(objRef);

		   	ChatRoom_impl chatRoomImpl = new ChatRoom_impl();
			ChatRoom chatroom = chatRoomImpl._this(orb);


			org.omg.CosNaming.NameComponent nc = new org.omg.CosNaming.NameComponent("chatroom","");
			org.omg.CosNaming.NameComponent path[] = {nc};
			ncRef.rebind(path, chatroom);

			org.omg.PortableServer.POA rootPOA = org.omg.PortableServer.POAHelper.narrow(orb.resolve_initial_references("RootPOA"));

			org.omg.PortableServer.POAManager manager = rootPOA.the_POAManager();

			manager.activate();
			orb.run();

		} catch (Exception ex) {
			System.out.println(ex);
			return 1;
		}

		return 0;
	}
}
