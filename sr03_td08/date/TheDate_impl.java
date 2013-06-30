// Java TheDate_impl.java
package date;

import java.util.Date;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;

public class TheDate_impl extends TheDatePOA {

	public String getTheDate() {

		String result;
		DateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");

		//get current date time with Date()
		Date date = new Date();

		result = dateFormat.format(date);
		System.out.println(result);

		return result;
	}
}

