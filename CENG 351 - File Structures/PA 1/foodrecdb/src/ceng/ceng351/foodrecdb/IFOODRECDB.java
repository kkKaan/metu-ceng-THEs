package ceng.ceng351.foodrecdb;

public interface IFOODRECDB {
    
    /**
    * Place your initialization code inside if required.
    * 
    * <p>
    * This function will be called before all other operations. If your implementation
    * need initialization , necessary operations should be done inside this function. For
    * example, you can set your connection to the database server inside this function.
    */
   public void initialize();
   
   /**
    * Should create the necessary tables when called.
    * 
    * @return the number of tables that are created successfully.
    */
   public int createTables();
   
   /**
    * Should drop the tables if exists when called. 
    * 
    * @return the number of tables are dropped successfully.
    */
   public int dropTables();
   
   /**
    * Should insert an array of MenuItem into the database.
    * 
    * @return Number of rows inserted successfully.
    */
   public int insertMenuItems(MenuItem[] items);

   /**
    * Should insert an array of Ingredient into the database.
    *
    * @return Number of rows inserted successfully.
    */

   public int insertIngredients(Ingredient[] ingredients);

   /**
    * Should insert an array of Includes into the database.
    *
    * @return Number of rows inserted successfully.
    */
   public int insertIncludes(Includes[] includes);
   
   /**
    * Should insert an array of DietaryCategory into the database.
    * 
    * @return Number of rows inserted successfully.
    */
   public int insertDietaryCategories(DietaryCategory[] categories);

   /**
    * Should insert an array of Seen into the database.
    * 
    * @return Number of rows inserted successfully.
    */

   public int insertRatings(Rating[] ratings);
   
   /**
    * Should return menu items that include the given ingredient
    * 
    * @return MenuItem[]
    */
   public MenuItem[] getMenuItemsWithGivenIngredient(String name);

   /**
    * Should return menu items that do not have any ingredients in the Includes table
    *
    * @return MenuItem[]
    */
   public MenuItem[] getMenuItemsWithoutAnyIngredient();
   

   /**
    * Should return ingredients that are not included in any menu item
    *
    * @return Ingredient[]
    */
   public Ingredient[] getNotIncludedIngredients();


   /**
    * Should return menu item with the highest different ingredient number
    *
    * @return MenuItem
    */
   public MenuItem getMenuItemWithMostIngredients();


   /**
    * Should return menu items with their ID, name, and average rating
    *
    * @return MenuItemAverageRatingResult[]
    */
   public QueryResult.MenuItemAverageRatingResult[] getMenuItemsWithAvgRatings();

   /**
    * Should return menu items that are suitable for a given dietary category
    *
    * @return MenuItem[]
    */
   public MenuItem[] getMenuItemsForDietaryCategory(String category);

   /**
    * Should return the most used ingredient across all menu items
    *
    * @return Ingredient
    */
   public Ingredient getMostUsedIngredient();


   /**
    * Should return cuisine names with their average ratings
    *
    * @return CuisineWithAverageResult[]
    */
   public QueryResult.CuisineWithAverageResult[] getCuisinesWithAvgRating();


   /**
    * Should return cuisine names with their average ingredient count per item
    *
    * @return CuisineWithAverageResult[]
    */
   public QueryResult.CuisineWithAverageResult[] getCuisinesWithAvgIngredientCount();


   /**
    * Should increase the price of all menu items that include the given ingredient by the given amount
    *
    * @return the row count for SQL Data Manipulation Language (DML) statements
    */
   public int increasePrice(String ingredientName, String increaseAmount);

   /**
    * Should delete and return ratings that have an earlier rating date than the given date
    *
    * @return Rating[]
    */
   public Rating[] deleteOlderRatings(String date);

}
