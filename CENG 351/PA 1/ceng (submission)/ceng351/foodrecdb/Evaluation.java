package ceng.ceng351.foodrecdb;

import ceng.ceng351.foodrecdb.QueryResult.MenuItemAverageRatingResult;
import ceng.ceng351.foodrecdb.QueryResult.CuisineWithAverageResult;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.text.DecimalFormat;
import java.util.Vector;


public class Evaluation {
    
    private static String user = "e1234567"; // TODO: Your userName
    private static String password = "dummyPassword"; //  TODO: Your password
    private static String host = "momcorp.ceng.metu.edu.tr"; // host name
    private static String database = "db1234567"; // TODO: Your database name
    private static int port = 8080; // port
    
    private static Connection connection = null;

    public static void connect() {
		
        String url = "jdbc:mysql://" + host + ":" + port + "/" + database;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection =  DriverManager.getConnection(url, user, password);
        } 
        catch (SQLException | ClassNotFoundException e) {
            e.printStackTrace();
        } 
    }
    
    public static void disconnect() {
		
        if (connection != null) {
            try {
                connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
    
    public static void addInputTitle(String title, BufferedWriter bufferedWriter) throws IOException {
        bufferedWriter.write("*** " + title + " ***" + System.getProperty("line.separator"));
    }

    private static final DecimalFormat df = new DecimalFormat("0.00");

    public static void printAllTables(BufferedWriter bufferedWriter) throws IOException {
		
        String sql1 = "show tables";
        String sql2 = "describe ";

        Vector<String> tables = new Vector<>();

        try
        {
            // Execute query
            Statement st = connection.createStatement();
            ResultSet rs = st.executeQuery(sql1);

            // Process the result set
            while(rs.next()) {
                tables.add(rs.getString(1));
            }

            for(int i=0; i < tables.size(); i++) {
                rs = st.executeQuery(sql2 + tables.get(i));

                // Print table name
                bufferedWriter.write("--- " + tables.get(i) + " ---" + System.getProperty("line.separator"));

                // Print field names and types
                while(rs.next()) {
                        bufferedWriter.write(rs.getString(1) + " " + rs.getString(2) + System.getProperty("line.separator"));
                }

                bufferedWriter.write(System.getProperty("line.separator"));
            }

        } catch (SQLException e) {
            printException(e);
        }
    }
    
    private static void printException(SQLException ex) {
        System.out.println(ex.getMessage() + "\n");
    }
	
    public static void printLine(String result, BufferedWriter bufferedWriter) throws IOException {
        bufferedWriter.write(result + System.getProperty("line.separator"));
    }

    public static void addDivider(BufferedWriter bufferedWriter) throws IOException {
        bufferedWriter.write( System.getProperty("line.separator")+ "--------------------------------------------------------------" + System.getProperty("line.separator"));
    }
    

    public static void main(String[] args) {

       int numberofInsertions = 0;
       int numberofTablesCreated = 0;
       int numberofTablesDropped = 0;

       /***********************************************************/
       // TODO While running on your local machine, change foodrecdbDirectory accordingly
       String foodrecdbDirectory = "/PATH/TO/foodrecdb/src" + System.getProperty("file.separator") +
               "ceng" + System.getProperty("file.separator") +
                       "ceng351" + System.getProperty("file.separator") +
                       "foodrecdb";
       /***********************************************************/

       FileWriter fileWriter = null;
       BufferedWriter bufferedWriter = null;

       //Connect to the database
       connect();

       // Create FOODRECDB object
       FOODRECDB foodrecDB = null;

       // Define arguments for the queries
       String givenIngredient = "bell_pepper";
       String givenDietaryCategory = "vegetarian";
       String givenPrice = "10";
       String givenDate = "2022-10-05";

       try {
            // Create FOODRECDB object and initialize
            foodrecDB = new FOODRECDB();
            foodrecDB.initialize();

            /***********************************************************/
            /*************Create File Writer starts*********************/
            /***********************************************************/
            fileWriter = FileOperations.createFileWriter(foodrecdbDirectory + System.getProperty("file.separator") + "output" + System.getProperty("file.separator") + "Output.txt");
            bufferedWriter =  new BufferedWriter(fileWriter);
            /***********************************************************/
            /*************Create File Writer ends***********************/
            /***********************************************************/

            /***********************************************************/
            /*************Drop tables starts****************************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("Drop tables", bufferedWriter);
            numberofTablesDropped = 0;

            // Drop tables
            try {
                numberofTablesDropped = foodrecDB.dropTables();
            } catch(Exception e) {
                e.printStackTrace();
            }

            // Check if tables are dropped
            printLine("Dropped " + numberofTablesDropped + " tables.", bufferedWriter);

            addDivider(bufferedWriter);
            /***********************************************************/
            /*************Drop tables ends******************************/
            /***********************************************************/

            /***********************************************************/
            /*******************Create tables starts********************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("Create tables",bufferedWriter);
            numberofTablesCreated = 0;

            // Create Tables
            try {
                numberofTablesCreated = foodrecDB.createTables();

                // Check if tables are created
                printLine("Created " + numberofTablesCreated + " tables.", bufferedWriter);

            } catch(Exception e) {
                printLine("createTables(): Exception occurred: \n\n" + e.toString(),bufferedWriter);
            }

            addDivider(bufferedWriter);
            /***********************************************************/
            /*******************Create tables ends**********************/
            /***********************************************************/

            /***********************************************************/
            /*******************Insert INTO MenuItems starts**********/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("Insert into MenuItems",bufferedWriter);
            //insert menu item
            numberofInsertions = 0;
            MenuItem[] items = FileOperations.readItemFile(foodrecdbDirectory +
                            System.getProperty("file.separator") + "data" + System.getProperty("file.separator") +
                            "Test_MenuItems.txt");

            numberofInsertions = foodrecDB.insertMenuItems(items);
            printLine( numberofInsertions + " menu items are inserted.",bufferedWriter);
            addDivider(bufferedWriter);
            /***********************************************************/
            /*******************Insert INTO MenuItems ends************/
            /***********************************************************/


           /***********************************************************/
           /*******************Insert INTO Ingredients starts*************/
           /***********************************************************/
           addDivider(bufferedWriter);
           addInputTitle("Insert into Ingredients",bufferedWriter);
           //insert ingredient
           numberofInsertions = 0;
           Ingredient[] ingredients = FileOperations.readIngredientFile(foodrecdbDirectory +
                   System.getProperty("file.separator") + "data" + System.getProperty("file.separator") +
                   "Test_Ingredients.txt");

           numberofInsertions = foodrecDB.insertIngredients(ingredients);
           printLine(numberofInsertions + " ingredients are inserted.",bufferedWriter);
           addDivider(bufferedWriter);
           /***********************************************************/
           /*******************Insert INTO Ingredients ends***************/
           /***********************************************************/

            /***********************************************************/
            /*******************Insert INTO Includes starts*****************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("Insert into Includes",bufferedWriter);
            //insert includes row
            numberofInsertions = 0;
            Includes[] includes = FileOperations.readIncludesFile( foodrecdbDirectory + System.getProperty("file.separator")
                    + "data" + System.getProperty("file.separator") + "Test_Includes.txt");

            numberofInsertions = foodrecDB.insertIncludes(includes);
            printLine( numberofInsertions + " includes rows are inserted.",bufferedWriter);
            addDivider(bufferedWriter);
            /***********************************************************/
            /*******************Insert INTO Includes ends*******************/
            /***********************************************************/

            /***********************************************************/
            /*******************Insert INTO Ratings starts**********/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("Insert into Ratings",bufferedWriter);
            //insert rating
            numberofInsertions = 0;
            Rating[] sideEffects = FileOperations.readRatingFile(foodrecdbDirectory +
                            System.getProperty("file.separator") + "data" + System.getProperty("file.separator") +
                            "Test_Ratings.txt");

            numberofInsertions = foodrecDB.insertRatings(sideEffects);
            printLine( numberofInsertions + " ratings are inserted.", bufferedWriter);
            addDivider(bufferedWriter);
            /***********************************************************/
            /*******************Insert INTO Ratings ends************/
            /***********************************************************/


            /***********************************************************/
            /*******************Insert INTO DietaryCategories starts*************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("Insert into DietaryCategories",bufferedWriter);
            //insert dietary category row
            numberofInsertions = 0;
            DietaryCategory[] categories = FileOperations.readDietaryCategoryFile(foodrecdbDirectory +
                            System.getProperty("file.separator") + "data" + System.getProperty("file.separator") +
                            "Test_DietaryCategories.txt");

            numberofInsertions = foodrecDB.insertDietaryCategories(categories);
            printLine(numberofInsertions + " dietary category rows are inserted.",bufferedWriter);
            addDivider(bufferedWriter);
            /***********************************************************/
            /*******************Insert INTO DietaryCategories ends***************/
            /***********************************************************/
            
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("List all menu items that include a given ingredient",bufferedWriter);
            try {

                MenuItem[] MenuItemResultArray1 = foodrecDB.getMenuItemsWithGivenIngredient(givenIngredient);

                //Header Line
                printLine("ItemID" + "\t" + "Name" + "\t" + "Cuisine" + "\t" + "Price",bufferedWriter);

                if(MenuItemResultArray1 != null) {
                    for(MenuItem MenuItem : MenuItemResultArray1){
                        printLine(MenuItem.toString(),bufferedWriter);
                    }	
                }


            } catch(Exception e) {
                printLine("getMenuItemsWithGivenIngredient(givenIngredient): Exception occurred: \n\n" + e.toString(),bufferedWriter);
            }
            addDivider(bufferedWriter);
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("List menu items that do not have any ingredients in the database",bufferedWriter);
            try {

                MenuItem[] MenuItemResultArray2 = foodrecDB.getMenuItemsWithoutAnyIngredient();

                //Header Line
                printLine("ItemID" + "\t" + "Name" + "\t" + "Cuisine" + "\t" + "Price",bufferedWriter);

                if(MenuItemResultArray2 != null) {
                    for(MenuItem MenuItem : MenuItemResultArray2){
                        printLine(MenuItem.toString(),bufferedWriter);
                    }
                }

            } catch(Exception e) {
                printLine("getMenuItemsWithoutAnyIngredient(): Exception occurred: \n\n" + e.toString(),bufferedWriter);
            }
            addDivider(bufferedWriter);
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
   
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("Find ingredients that have not been included in any menu items",bufferedWriter);
            try {

                Ingredient[] IngredientResultArray1 = foodrecDB.getNotIncludedIngredients();

                //Header Line
                printLine("ingredientID" + "\t" + "Name",bufferedWriter);

                if(IngredientResultArray1 != null) {
                    for(Ingredient Ingredient : IngredientResultArray1){
                        printLine(Ingredient.toString(),bufferedWriter);
                    }
                }

            } catch(Exception e) {
                printLine("getNotIncludedIngredients(): Exception occurred: \n\n" + e.toString(),bufferedWriter);
            }

            addDivider(bufferedWriter);
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            
            
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("Find the menu item that includes the biggest count of ingredients",bufferedWriter);
            try {

                MenuItem menuItem = foodrecDB.getMenuItemWithMostIngredients();

                //Header Line
                printLine("ItemID" + "\t" + "Name" + "\t" + "Cuisine" + "\t" + "Price",bufferedWriter);

                if(menuItem != null) {
                    printLine(menuItem.toString(),bufferedWriter);
                }
            } catch(Exception e) {
                printLine("getMenuItemWithMostIngredients(): Exception occurred: \n\n" + e.toString(),bufferedWriter);
            }
            addDivider(bufferedWriter);
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/

            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("List the average rating of each menu item",bufferedWriter);
            try {

                QueryResult.MenuItemAverageRatingResult[] MenuItemAverageRatingResultArray = foodrecDB.getMenuItemsWithAvgRatings();

                //Header Line
                printLine("ItemID" + "\t" + "Name" + "\t" + "Average Rating",bufferedWriter);

                if(MenuItemAverageRatingResultArray != null) {
                    for(QueryResult.MenuItemAverageRatingResult MenuItemAverageRatingResult : MenuItemAverageRatingResultArray){
                        printLine(MenuItemAverageRatingResult.toString(),bufferedWriter);
                    }
                }


            } catch(Exception e) {
                printLine("getMenuItemsWithAvgRatings(): Exception occurred: \n\n" + e.toString(),bufferedWriter);
            }
            addDivider(bufferedWriter);
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("List menu items suitable to a given dietary category",bufferedWriter);
            try {

                MenuItem[] MenuItemResultArray3  = foodrecDB.getMenuItemsForDietaryCategory(givenDietaryCategory);

                //Header Line
                printLine("ItemID" + "\t" + "Name" + "\t" + "Cuisine" + "\t" + "Price",bufferedWriter);

                if(MenuItemResultArray3 != null) {
                    for(MenuItem MenuItem : MenuItemResultArray3){
                        printLine(MenuItem.toString(),bufferedWriter);
                    }
                }

            } catch(Exception e) {
                printLine("getMenuItemsForDietaryCategory(): Exception occurred: \n\n" + e.toString(),bufferedWriter);
            }
            addDivider(bufferedWriter);
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("Find the most used ingredient across all menu items",bufferedWriter);

            try {

                Ingredient ingredient = foodrecDB.getMostUsedIngredient();
                //Header Line
                printLine("ingredientID" + "\t" + "Name",bufferedWriter);
                
                if (ingredient != null) {
                    printLine(ingredient.toString(),bufferedWriter);
                }

            } catch(Exception e) {
                printLine("getMostUsedIngredient(): Exception occurred: \n\n" + e.toString(),bufferedWriter);
            }
            addDivider(bufferedWriter);
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("List the cuisines with the average rating of menu items belonging to that cuisine",bufferedWriter);
            try {

                QueryResult.CuisineWithAverageResult[] CuisineWithAverageResultArray1 = foodrecDB.getCuisinesWithAvgRating();

                //Header Line
                printLine("Cuisine" + "\t" + "Average Rating", bufferedWriter);

                if(CuisineWithAverageResultArray1 != null) {
                    for(QueryResult.CuisineWithAverageResult CuisineWithAverageResult : CuisineWithAverageResultArray1){
                        printLine(CuisineWithAverageResult.toString(),bufferedWriter);
                    }
                }

            } catch(Exception e) {
                printLine("getCuisinesWithAvgRating(): Exception occurred: \n\n" + e.toString(),bufferedWriter);
            }
            addDivider(bufferedWriter);
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/

            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("List the cuisines with average ingredient count of menu items for each cuisine",bufferedWriter);
            try {

                QueryResult.CuisineWithAverageResult[] CuisineWithAverageResultArray2 = foodrecDB.getCuisinesWithAvgIngredientCount();

                //Header Line
                printLine("Cuisine" + "\t" + "Average Ingredient Count Per Item", bufferedWriter);

                if(CuisineWithAverageResultArray2 != null) {
                   for(QueryResult.CuisineWithAverageResult CuisineWithAverageResult : CuisineWithAverageResultArray2){
                       printLine(CuisineWithAverageResult.toString(),bufferedWriter);
                   }
                }

            }   catch(Exception e) {
                    printLine("getCuisinesWithAvgIngredientCount(): Exception occurred: \n\n" + e.toString(),bufferedWriter);
                }
            addDivider(bufferedWriter);
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/

            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("Increase the price of all menu items that include a given ingredient by a given amount",bufferedWriter);
            try {
                
                int numberofChanged = foodrecDB.increasePrice(givenIngredient, givenPrice);
		        printLine( numberofChanged + " rows are changed.", bufferedWriter);

            } catch(Exception e) {
                printLine("increasePrice: Exception occurred: \n\n" + e.toString(),bufferedWriter);
            }
            addDivider(bufferedWriter);
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/

            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("Delete all ratings that have an earlier rating date than the given date",bufferedWriter);
            try {
                
                Rating[] RatingResultArray = foodrecDB.deleteOlderRatings(givenDate);

                //Header Line
                printLine("RatingID" + "\t" + "ItemID" + "\t" + "Rating" + "\t" + "Rating Date",bufferedWriter);

                if(RatingResultArray != null) {
                    for(Rating Rating : RatingResultArray){
                        printLine(Rating.toString(),bufferedWriter);
                    }
                }
            } catch(Exception e) {
                printLine("deleteOlderRatings(): Exception occurred: \n\n" + e.toString(),bufferedWriter);
            }
            addDivider(bufferedWriter);
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/

       } catch (IOException e) {
               e.printStackTrace();
       } finally {
           try {
                //Close Writer
                if (bufferedWriter != null) {
                    bufferedWriter.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
            //Close Connection
            //disconnect();
       }
    }
    
}
