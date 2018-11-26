/*
 * Sources:
 * 		ResultPairs from UrlValidatorTest.java from UrlValidatorCorrect
 */

import junit.framework.TestCase;
import java.io.PrintWriter;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!

public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }
   
   public void testManualTest(){
	   //You can use this function to implement your manual testing	   
	   
   }
   
   public void testYourFirstPartition(){
	   //You can use this function to implement your First Partition testing	   
   }
   
   public void testYourSecondPartition(){
	   //You can use this function to implement your Second Partition testing	   
   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid(){
	   PrintWriter file = null;
	   try{
		   file = new PrintWriter("testIsValidresults.out", "UTF-8");
	   }
	   catch(Exception | Error e) {
		   System.out.println(e);
	   }
	   
	   UrlValidator urlVal = null;
	   
	   file.println("--------------- Begin Programming Based Testing ---------------");
	   file.println();
	   file.println("--------------------- Test Default Params ---------------------");
	   
	   urlVal = new UrlValidator();
	   testUrlScheme[3].valid = false;
	   tests(urlVal, false, file);
	   testUrlScheme[3].valid = true;
	   
	   file.println();
	   file.println("--------------------- Test Defined Schemes --------------------");
	   
	   String schemes[] = {"http", "ftp"};
	   
	   testUrlScheme[2].valid = false;
	   testUrlScheme[3].valid = false;
	   urlVal = new UrlValidator(schemes);
	   tests(urlVal, false, file);
	   testUrlScheme[2].valid = true;
	   testUrlScheme[3].valid = true;
	   
	   file.println();
	   file.println("------------------------ Test Options -------------------------");
	   
	   long options = UrlValidator.ALLOW_ALL_SCHEMES + 
			   UrlValidator.ALLOW_2_SLASHES + 
			   UrlValidator.NO_FRAGMENTS + 
			   UrlValidator.ALLOW_LOCAL_URLS;
	   
	   urlVal = new UrlValidator(options);
	   testUrlAuthority[2].valid = true;
	   tests(urlVal, true, file);
	   testUrlAuthority[2].valid = false;
	   
	   file.println();
	   file.println("--------------- Test Defined Schemes & Options ----------------");
	   
	   testUrlScheme[2].valid = false;
	   testUrlScheme[3].valid = false;
	   testUrlAuthority[2].valid = true;
	   urlVal = new UrlValidator(schemes, options - UrlValidator.ALLOW_ALL_SCHEMES);
	   tests(urlVal, true, file);
	   testUrlScheme[2].valid = true;
	   testUrlScheme[3].valid = true;
	   testUrlAuthority[2].valid = false;
	   
	   file.println();
	   file.println("---------------- End Programming Based Testing ----------------");
	   
	   file.close();
   }   
   
   public void tests(UrlValidator urlVal, boolean options, PrintWriter file) {
	   String testUrl;
	   boolean validity;
	   boolean result = true;
	   boolean exception = false;
	   ResultPair[] path;
	   
	   if(options == true) {
		   path = testUrlPathOptions;
		   try {
			   result = urlVal.isValid("http://localhost:8080/");
		   }
		   catch(Exception | Error e) {
			   file.println("BASELINE FAIL: http://localhost:8080/ caused "+e);
			   exception = true;
		   }
		   if(result == false && exception == false) {
			   file.println("BASELINE FAIL: http://localhost:8080/ should be valid");
		   }
		   exception = false;
	   }
	   else {
		   path = testUrlPath;
	   }
	   
	   try {
		   result = urlVal.isValid("http://www.google.com/");
	   }
	   catch(Exception | Error e) {
		   file.println("BASELINE FAIL: http://www.google.com/ caused "+e);
		   exception = true;
	   }
	   if(result == false && exception == false) {
		   file.println("BASELINE FAIL: http://www.google.com/ should be valid");
	   }
	   exception = false;
	   
	   try {
		   result = urlVal.isValid(null);
	   }
	   catch(Exception | Error e) {
		   file.println("BASELINE FAIL: null caused "+e);
		   exception = true;
	   }
	   if(result == true && exception == false) {
		   file.println("BASELINE FAIL: null should be invalid");
	   }
	   exception = false;
	   
	   for(int i = 0; i < testUrlScheme.length; i++) {
		   for(int j = 0; j < testUrlAuthority.length; j++) {
			   for(int k = 0; k < testUrlPort.length; k++) {
				   for(int m = 0; m < path.length; m++) {
					   for(int n = 0; n < testUrlQuery.length; n++) {
						   testUrl = testUrlScheme[i].item + testUrlAuthority[j].item + testUrlPort[k].item + path[m].item + testUrlQuery[n].item;
						   validity = (testUrlScheme[i].valid && testUrlAuthority[j].valid && testUrlPort[k].valid && path[m].valid && testUrlQuery[n].valid);
					   
						   try {
							   result = urlVal.isValid(testUrl);
						   }
						   catch(Exception | Error e) {
							   file.println("FAIL: "+testUrl+" caused "+e);
							   exception = true;
						   }
						   
						   if(result == false && validity == true && exception == false) {
							   file.println("FAIL: "+testUrlScheme[i].item+"("+testUrlScheme[i].valid+") "+testUrlAuthority[j].item+"("+testUrlAuthority[j].valid+") "+testUrlPort[k].item+"("+testUrlPort[k].valid+") "+path[m].item+"("+path[m].valid+") "+testUrlQuery[n].item+"("+testUrlQuery[n].valid+") "+" in "+testUrl+" should be valid");
						   }
						   else if(result == true && validity == false && exception == false) {
							   file.println("FAIL: "+testUrlScheme[i].item+"("+testUrlScheme[i].valid+") "+testUrlAuthority[j].item+"("+testUrlAuthority[j].valid+") "+testUrlPort[k].item+"("+testUrlPort[k].valid+") "+path[m].item+"("+path[m].valid+") "+testUrlQuery[n].item+"("+testUrlQuery[n].valid+") "+" in "+testUrl+" should be invalid");
						   }
						   
						   exception = false;
					   } 
				   } 
			   } 
		   }  
	   }	   
   }
 //-------------------- Test data for creating a composite URL
   /**
    * The data given below approximates the 4 parts of a URL
    * <scheme>://<authority><path>?<query> except that the port number
    * is broken out of authority to increase the number of permutations.
    * A complete URL is composed of a scheme+authority+port+path+query,
    * all of which must be individually valid for the entire URL to be considered
    * valid.
    */
   ResultPair[] testUrlScheme = {new ResultPair("http://", true),
                               new ResultPair("ftp://", true),
                               new ResultPair("https://", true),
                               new ResultPair("h3t://", true),
                               new ResultPair("3ht://", false),
                               new ResultPair("http:/", false),
                               new ResultPair("http:", false),
                               new ResultPair("http/", false),
                               new ResultPair("://", false)};

   ResultPair[] testUrlAuthority = {new ResultPair("www.google.com", true),
                                  new ResultPair("google.com", true),
                                  new ResultPair("aaa", false),
                                  new ResultPair("go.au", true),
                                  new ResultPair("www..com", false),
                                  new ResultPair("www.amazon", false),
                                  new ResultPair("0.0.0.0", true),
                                  new ResultPair("255.255.255.255", true),
                                  new ResultPair("256.256.256.256", false),
                                  new ResultPair("255.com", true),
                                  new ResultPair("1.2.3.4.5", false),
                                  new ResultPair("1.2.3.4.", false),
                                  new ResultPair("1.2.3", false),
                                  new ResultPair(".1.2.3.4", false),
                                  new ResultPair("google.ala", false),
                                  new ResultPair("aaa.", false),
                                  new ResultPair(".aaa", false)
   };
   ResultPair[] testUrlPort = {new ResultPair(":80", true),
                             new ResultPair(":65535", true),
                             new ResultPair(":0", true),
                             new ResultPair(":-1", false),
                            new ResultPair(":65636",false),
                             new ResultPair(":65a", false)
   };
   ResultPair[] testUrlPath = {new ResultPair("/test1", true),
                          new ResultPair("/t123", true),
                          new ResultPair("/$23", true),
                          new ResultPair("/..", false),
                          new ResultPair("/../", false),
                          new ResultPair("/test1/", true),
                          new ResultPair("", true),
                          new ResultPair("/test1/file", true),
                          new ResultPair("/..//file", false),
                          new ResultPair(null, false),
                          new ResultPair("/test1//file", false)
   };
   //Test allow2slash, noFragment
   ResultPair[] testUrlPathOptions = {new ResultPair("/test1", true),
                                    new ResultPair("/t123", true),
                                    new ResultPair("/$23", true),
                                    new ResultPair("/..", false),
                                    new ResultPair("/../", false),
                                    new ResultPair("/test1/", true),
                                    new ResultPair("/#", false),
                                    new ResultPair("", true),
                                    new ResultPair("/test1/file", true),
                                    new ResultPair("/t123/file", true),
                                    new ResultPair("/$23/file", true),
                                    new ResultPair("/../file", false),
                                    new ResultPair("/..//file", false),
                                    new ResultPair("/test1//file", true),
                                    new ResultPair("/#/file", false)
   };
   
   ResultPair[] testUrlQuery = {new ResultPair("", true),
		   new ResultPair("?action*view", false),
           new ResultPair("?action=edit&mode=up", true)
   };
}
