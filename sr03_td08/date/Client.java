// Java 2  Client.java
package date;

public class Client {

	public static void main(String args[]) {

		// Same as the server
		java.util.Properties props = System.getProperties();
		props.put("org.omg.CORBA.ORBClass", "com.ooc.OBServer.ORB");
		props.put("org.omg.CORBA.ORBSingletonClass", "com.ooc.CORBA.ORBSingleton");

		int status = 0;
		org.omg.CORBA.ORB orb = null;

		try {
			orb = org.omg.CORBA.ORB.init(args, props);
			status = run(orb);
		} catch(Exception ex) {
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
	static int run(org.omg.CORBA.ORB orb) {

		try {
			org.omg.CORBA.Object objRef = orb.resolve_initial_references("NameService");
			org.omg.CosNaming.NamingContext ncRef = org.omg.CosNaming.NamingContextHelper.narrow(objRef);

			org.omg.CosNaming.NameComponent nc = new org.omg.CosNaming.NameComponent("date","");
			org.omg.CosNaming.NameComponent path[] = {nc};
			TheDate theDateRef = TheDateHelper.narrow(ncRef.resolve(path));


			String d = theDateRef.getTheDate();

		} catch(Exception ex) {
			System.out.println(ex);
			return 1;
		}

		return 0;
	}
}
