package ceng.ceng351.foodrecdb;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class FOODRECDB implements IFOODRECDB
{
    private static String user = "";// username;
    private static String password = ""; //  TODO: Your password
    private static String host = "momcorp.ceng.metu.edu.tr"; // host name
    private static String database = "dbe1234567"; // TODO: Your database name
    private static int port = 8080; // port

    private Connection connection;

    public FOODRECDB()
    {
        // TODO Auto-generated constructor stub
    }
    @Override
    public void initialize()
    {
        String url = "jdbc:mysql://" + this.host + ":" + this.port + "/" + this.database;

        try
        {
            Class.forName("com.mysql.cj.jdbc.Driver");
            this.connection =  DriverManager.getConnection(url, this.user, this.password);
        }
        catch (SQLException | ClassNotFoundException e)
        {
            e.printStackTrace();
        }
    }

    @Override
    public int createTables()
    {
        int result;
        int numOfTables = 0;

        String[] queries =
        {
            "CREATE TABLE IF NOT EXISTS MenuItems (itemID INT NOT NULL, " +
                                                    "itemName VARCHAR(40), " +
                                                    "cuisine VARCHAR(20), " +
                                                    "price INT, " +
                                                    "PRIMARY KEY (itemID));",
            "CREATE TABLE IF NOT EXISTS Ingredients (ingredientID INT NOT NULL, " +
                                                      "ingredientName VARCHAR(40), " +
                                                      "PRIMARY KEY (ingredientID));",
            "CREATE TABLE IF NOT EXISTS Includes (itemID INT NOT NULL," +
                                                   "ingredientID INT NOT NULL, " +
                                                   "PRIMARY KEY (itemID, ingredientID), " +
                                                   "FOREIGN KEY (itemID) REFERENCES MenuItems(itemID) ON DELETE CASCADE ON UPDATE CASCADE, " +
                                                   "FOREIGN KEY (ingredientID) REFERENCES Ingredients(ingredientID) ON DELETE CASCADE ON UPDATE CASCADE);",
            "CREATE TABLE IF NOT EXISTS Ratings (ratingID INT NOT NULL, " +
                                                  "itemID INT NOT NULL, " +
                                                  "rating INT, " +
                                                  "ratingDate DATE, " +
                                                  "PRIMARY KEY (ratingID), " +
                                                  "FOREIGN KEY (itemID) REFERENCES MenuItems(itemID) ON DELETE CASCADE ON UPDATE CASCADE);",
            "CREATE TABLE IF NOT EXISTS DietaryCategories (ingredientID INT NOT NULL, " +
                                                            "dietaryCategory VARCHAR(20) NOT NULL, " +
                                                            "PRIMARY KEY (ingredientID, dietaryCategory), " +
                                                            "FOREIGN KEY (`ingredientID`) REFERENCES `Ingredients`(`ingredientID`) ON DELETE CASCADE ON UPDATE CASCADE);"
        };

        for(String s:queries)
        {
            try
            {
                Statement statement = this.connection.createStatement();
                result = statement.executeUpdate(s);
                System.out.println(result);
                ++numOfTables;
                statement.close();
            }
            catch (SQLException e)
            {
                e.printStackTrace();
            }
        }
        return numOfTables;
    }

    @Override
    public int dropTables()
    {
        int result;
        int numOfTables = 0;
        String[] tableNames = {"Includes", "Ratings", "DietaryCategories", "MenuItems", "Ingredients"};
        String queryDropTable = "DROP TABLE IF EXISTS `";

        for(String t:tableNames)
        {
            try
            {
                Statement statement = this.connection.createStatement();
                result = statement.executeUpdate(queryDropTable + t + "`");
                ++numOfTables;
                System.out.println(result);
                statement.close();
            }
            catch (SQLException e)
            {
                e.printStackTrace();
            }
        }
        return numOfTables;
    }

    @Override
    public int insertMenuItems(MenuItem[] items)
    {
        int result;
        int noOfIns = 0;

        for(MenuItem i:items)
        {
            try
            {
                Statement statement = this.connection.createStatement();

                String query = "INSERT INTO MenuItems (itemID, itemName, cuisine, price) VALUES ('"+i.getItemID()+"', '"+i.getItemName()+"', '"+i.getCuisine()+"', '"+i.getPrice()+"');";
                result = statement.executeUpdate(query);

                ++noOfIns;

                System.out.println(result);
                statement.close();
            }
            catch (SQLException e)
            {
                e.printStackTrace();
            }
        }
        return noOfIns;
    }

    @Override
    public int insertIngredients(Ingredient[] ingredients)
    {
        int result;
        int noOfIns = 0;

        for(Ingredient i:ingredients)
        {
            try
            {
                Statement statement = this.connection.createStatement();

                String query = "INSERT INTO Ingredients (ingredientID, ingredientName) VALUES ('"+i.getIngredientID()+"', '"+i.getIngredientName()+"');";
                result = statement.executeUpdate(query);

                ++noOfIns;

                System.out.println(result);
                statement.close();
            }
            catch (SQLException e)
            {
                e.printStackTrace();
            }
        }
        return noOfIns;
    }

    @Override
    public int insertIncludes(Includes[] includes)
    {
        int result;
        int noOfIns = 0;

        for(Includes i:includes)
        {
            try
            {
                Statement statement = this.connection.createStatement();

                String query = "INSERT INTO Includes (itemID, ingredientID) VALUES ('"+i.getItemID()+"', '"+i.getIngredientID()+"');";
                result = statement.executeUpdate(query);

                ++noOfIns;

                System.out.println(result);
                statement.close();
            }
            catch (SQLException e)
            {
                e.printStackTrace();
            }
        }
        return noOfIns;
    }

    @Override
    public int insertDietaryCategories(DietaryCategory[] categories)
    {
        int result;
        int noOfIns = 0;

        for(DietaryCategory i:categories)
        {
            try
            {
                Statement statement = this.connection.createStatement();

                String query = "INSERT INTO DietaryCategories (ingredientID, dietaryCategory) VALUES ('"+i.getIngredientID()+"', '"+i.getDietaryCategory()+"');";
                result = statement.executeUpdate(query);

                ++noOfIns;

                System.out.println(result);
                statement.close();
            }
            catch (SQLException e)
            {
                e.printStackTrace();
            }
        }
        return noOfIns;
    }

    @Override
    public int insertRatings(Rating[] ratings)
    {
        int result;
        int noOfIns = 0;

        for(Rating i:ratings)
        {
            try
            {
                Statement statement = this.connection.createStatement();

                String query = "INSERT INTO Ratings (ratingID, itemID, rating, ratingDate) VALUES ('"+i.getRatingID()+"', '"+i.getItemID()+"', '"+i.getRating()+"', '"+i.getRatingDate()+"');";
                result = statement.executeUpdate(query);

                ++noOfIns;

                System.out.println(result);
                statement.close();
            }
            catch (SQLException e)
            {
                e.printStackTrace();
            }
        }
        return noOfIns;
    }

    @Override
    public MenuItem[] getMenuItemsWithGivenIngredient(String name)
    {
        ResultSet rs;
        MenuItem[] items = null;

        String query = "select distinct m.itemID, m.itemName, m.cuisine, m.price " +
                       "from MenuItems m, Includes inc, Ingredients ing " +
                       "where m.itemID = inc.itemID " +
                       "and inc.ingredientID = ing.ingredientID " +
                       "and ing.ingredientName = '" + name + "' " +
                       "order by m.itemID asc;";

        try
        {
            Statement st  = this.connection.createStatement();
            rs = st.executeQuery(query);
            int rows = 0;
            if(rs.last())
            {
                rows = rs.getRow();
                rs.beforeFirst(); // not rs.first() because the rs.next() in while will move on, skip the first element
            }

            items = new MenuItem[rows];
            int i = 0;

            while(rs.next())
            {
                int itemID = rs.getInt("itemID");
                String itemN = rs.getString("itemName");
                String itemC = rs.getString("cuisine");
                int itemP = rs.getInt("price");

                MenuItem it = new MenuItem(itemID, itemN, itemC, itemP);
                items[i] = it;
                ++i;
            }
            st.close();
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
        return items;
    }

    @Override
    public MenuItem[] getMenuItemsWithoutAnyIngredient()
    {
        ResultSet rs;
        MenuItem[] items = null;

        String query = "select distinct m.itemID, m.itemName, m.cuisine, m.price " +
                       "from MenuItems m " +
                       "where m.itemID not in (select distinct itemID from Includes) " +
                       "order by m.itemID asc;";

        try
        {
            Statement st  = this.connection.createStatement();
            rs = st.executeQuery(query);
            int rows = 0;
            if(rs.last())
            {
                rows = rs.getRow();
                rs.beforeFirst();
            }

            items = new MenuItem[rows];
            int i = 0;

            while(rs.next())
            {
                int itemID = rs.getInt("itemID");
                String itemN = rs.getString("itemName");
                String itemC = rs.getString("cuisine");
                int itemP = rs.getInt("price");

                MenuItem it = new MenuItem(itemID, itemN, itemC, itemP);
                items[i] = it;
                ++i;
            }
            st.close();
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
        return items;
    }

    @Override
    public Ingredient[] getNotIncludedIngredients()
    {
        ResultSet rs;
        Ingredient[] items = null;

        String query = "select distinct ing.ingredientID, ing.ingredientName " +
                       "from Ingredients ing " +
                       "where ing.ingredientID not in (select distinct ingredientID from Includes) " +
                       "order by ing.ingredientID asc;";

        try
        {
            Statement st  = this.connection.createStatement();
            rs = st.executeQuery(query);
            int rows = 0;
            if(rs.last())
            {
                rows = rs.getRow();
                rs.beforeFirst();
            }

            items = new Ingredient[rows];
            int i = 0;

            while(rs.next())
            {
                int ingID = rs.getInt("ingredientID");
                String ingN = rs.getString("ingredientName");

                Ingredient it = new Ingredient(ingID, ingN);
                items[i] = it;
                ++i;
            }
            st.close();
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
        return items;
    }

    @Override
    public MenuItem getMenuItemWithMostIngredients()
    {
        ResultSet rs;
        MenuItem item = null;

        String query = "select distinct m.itemID, m.itemName, m.cuisine, m.price, count(*) as numIng " +
                       "from MenuItems m, Includes inc " +
                       "where m.itemID = inc.itemID " +
                       "group by m.itemID " +
                       "order by numIng desc " +
                       "limit 1;";

        String query2 = "select m.itemID, m.itemName, m.cuisine, m.price " +
                        "from MenuItems m, Includes inc " +
                        "where m.itemID = inc.itemID " +
                        "group by m.itemID, m.itemName " +
                        "having count(*) = (select max(numIngredients) " +
                        "                   from (select count(*) as numIngredients " +
                        "                         from MenuItems m1, Includes inc1 " +
                        "                         where m1.itemID = inc1.itemID " +
                        "                         group by m1.itemID, m1.itemName) x);";

        try
        {
            Statement st  = this.connection.createStatement();
            rs = st.executeQuery(query2);
            rs.next();

            int itemID = rs.getInt("itemID");
            String itemN = rs.getString("itemName");
            String itemC = rs.getString("cuisine");
            int itemP = rs.getInt("price");

            item = new MenuItem(itemID, itemN, itemC, itemP);

            st.close();
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
        return item;
    }

    @Override
    public QueryResult.MenuItemAverageRatingResult[] getMenuItemsWithAvgRatings()
    {
        ResultSet rs;
        QueryResult.MenuItemAverageRatingResult[] items = null;

        String query = "select distinct m.itemID, m.itemName, avg(cast(r.rating as float)) as average " +
                       "from MenuItems m, Ratings r " +
                       "where m.itemID = r.itemID " +
                       "group by m.itemID " +
                       "union " +
                       "select distinct m1.itemID, m1.itemName, null as average " +
                       "from MenuItems m1 " +
                       "where m1.itemID not in (select distinct r1.itemID from Ratings r1) " +
                       "order by average desc;";

        try
        {
            Statement st  = this.connection.createStatement();
            rs = st.executeQuery(query);
            int rows = 0;
            if(rs.last())
            {
                rows = rs.getRow();
                rs.beforeFirst();
            }

            items = new QueryResult.MenuItemAverageRatingResult[rows];
            int i = 0;

            while(rs.next())
            {
                int itemID = rs.getInt("itemID");
                String itemN = rs.getString("itemName");
                String avgRate = rs.getString("average");

                QueryResult.MenuItemAverageRatingResult it = new QueryResult.MenuItemAverageRatingResult(""+itemID, itemN, avgRate);
                items[i] = it;
                ++i;
            }
            st.close();
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
        return items;
    }

    @Override
    public MenuItem[] getMenuItemsForDietaryCategory(String category)
    {
        ResultSet rs;
        MenuItem[] items = null;

        String query = "select distinct m.itemID, m.itemName, m.cuisine, m.price " +
                       "from MenuItems m, Includes inc, DietaryCategories d " +
                       "where m.itemID = inc.itemID " +
                       "and inc.ingredientID = d.ingredientID " +
                       // "and d.ingredientID = ing.ingredientID " + ??????????????????????????
                       "and d.dietaryCategory = '" + category + "' " +
                       "group by m.itemID " +
                       "having count(*) = (select count(*) from Includes where itemID = m.itemID) " +
                       "order by m.itemID asc;";

        try
        {
            Statement st  = this.connection.createStatement();
            rs = st.executeQuery(query);
            int rows = 0;
            if(rs.last())
            {
                rows = rs.getRow();
                rs.beforeFirst();
            }

            items = new MenuItem[rows];
            int i = 0;

            while(rs.next())
            {
                int itemID = rs.getInt("itemID");
                String itemN = rs.getString("itemName");
                String itemC = rs.getString("cuisine");
                int itemP = rs.getInt("price");

                MenuItem it = new MenuItem(itemID, itemN, itemC, itemP);
                items[i] = it;
                ++i;
            }
            st.close();
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
        return items;
    }

    @Override
    public Ingredient getMostUsedIngredient()
    {
        ResultSet rs;
        Ingredient ing = null;

        String query = "select distinct ing.ingredientID, ing.ingredientName, count(*) as numIng " +
                       "from Ingredients ing, Includes inc " +
                       "where ing.ingredientID = inc.ingredientID " +
                       "group by ing.ingredientID " +
                       "order by numIng desc " +
                       "limit 1;";

        String query2 = "select distinct ing1.ingredientID, ing1.ingredientName " +
                        "from Ingredients ing1, Includes inc1 " +
                        "where ing1.ingredientID = inc1.ingredientID " +
                        "group by ing1.ingredientID, ing1.ingredientName " +
                        "having count(*) = (select max(numIng) " +
                                            "from " +
                                            "(select distinct ing.ingredientID, ing.ingredientName, count(*) as numIng " +
                                            "from Ingredients ing, Includes inc " +
                                            "where ing.ingredientID = inc.ingredientID " +
                                            "group by ing.ingredientID) x) ";

        try
        {
            Statement st  = this.connection.createStatement();
            rs = st.executeQuery(query2);
            rs.next();

            int ingID = rs.getInt("ingredientID");
            String ingN = rs.getString("ingredientName");

            ing = new Ingredient(ingID, ingN);

            st.close();
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
        return ing;
    }

    @Override
    public QueryResult.CuisineWithAverageResult[] getCuisinesWithAvgRating()
    {
        ResultSet rs;
        QueryResult.CuisineWithAverageResult[] items = null;

        String query = "select distinct m.cuisine as cuisineName, avg(cast(r.rating as float)) as average " +
                       "from MenuItems m, Ratings r " +
                       "where m.itemID = r.itemID " +
                       "group by m.cuisine " +
                       "union " +
                       "select distinct m1.cuisine as cuisineName, NULL as average " +
                       "from MenuItems m1 " +
                       "group by m1.cuisine " +
                       "having 1 > (select count(itemID) from MenuItems m2 where m2.cuisine = m1.cuisine and m2.itemID in (select r2.itemID from Ratings r2)) " +
                       "order by average desc;";

        try
        {
            Statement st  = this.connection.createStatement();
            rs = st.executeQuery(query);
            int rows = 0;
            if(rs.last())
            {
                rows = rs.getRow();
                rs.beforeFirst();
            }

            items = new QueryResult.CuisineWithAverageResult[rows];
            int i = 0;

            while(rs.next())
            {
                String cN = rs.getString("cuisineName");
                String avgRate = rs.getString("average");

                QueryResult.CuisineWithAverageResult it = new QueryResult.CuisineWithAverageResult(cN, avgRate);
                items[i] = it;
                ++i;
            }
            st.close();
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
        return items;
    }

    @Override
    public QueryResult.CuisineWithAverageResult[] getCuisinesWithAvgIngredientCount()
    {
        ResultSet rs;
        QueryResult.CuisineWithAverageResult[] items = null;

        String query = "select distinct ingCounts.cuisineName, (ingCounts.cnt / idCounts.cnt) as average " +
                       "from MenuItems mm, " +
                           "(select distinct m.cuisine as cuisineName, cast(count(*) as float) as cnt " +
                           "from MenuItems m, Includes inc " +
                           "where m.itemID = inc.itemID " +
                           "group by m.cuisine " +
                           "union " +
                           "select distinct m1.cuisine as cuisineName, 0 as average " +
                           "from MenuItems m1 " +
                           "group by m1.cuisine " +
                           "having 1 > (select count(itemID) from MenuItems m2 where m2.cuisine = m1.cuisine and m2.itemID in (select inc1.itemID from Includes inc1))) ingCounts, " +
                           "(select m3.cuisine as cuisineName, count(m3.itemID) as cnt " +
                           "from MenuItems m3 " +
                           "group by m3.cuisine) idCounts " +
                       "where mm.cuisine = ingCounts.cuisineName " +
                       "and ingCounts.cuisineName = idCounts.cuisineName " +
                       "order by average desc;";
        try
        {
            Statement st  = this.connection.createStatement();
            rs = st.executeQuery(query);
            int rows = 0;
            if(rs.last())
            {
                rows = rs.getRow();
                rs.beforeFirst();
            }

            items = new QueryResult.CuisineWithAverageResult[rows];
            int i = 0;

            while(rs.next())
            {
                String cN = rs.getString("cuisineName");
                String avgRate = rs.getString("average");

                QueryResult.CuisineWithAverageResult it = new QueryResult.CuisineWithAverageResult(cN, avgRate);
                items[i] = it;
                ++i;
            }
            st.close();
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
        return items;
    }

    @Override
    public int increasePrice(String ingredientName, String increaseAmount)
    {
        int res=0;

        String query = "update MenuItems set price = price + '" + increaseAmount + "' " +
                       "where itemID in (select inc.itemID from Includes inc, Ingredients ing where inc.ingredientID = ing.ingredientID and ing.ingredientName = '" + ingredientName + "' )";
        try
        {
            Statement st = this.connection.createStatement();
            res = st.executeUpdate(query);
            st.close();
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
        return res;
    }

    @Override
    public Rating[] deleteOlderRatings(String date)
    {
        ResultSet rs1;
        int rs2;
        Rating[] res = null;
        int n=0;

        // String query1 = "select from Ratings r where cast(r.ratingDate as date) < cast('"+date+"' as date);";
        String query1 = "select * from Ratings r where r.ratingDate < '"+date+"'; ";
        String query2 = "delete from Ratings r where r.ratingDate < '"+date+"'; ";

        try
        {
            Statement st = this.connection.createStatement();
            rs1 = st.executeQuery(query1);

            int rows = 0;
            if(rs1.last())
            {
                rows = rs1.getRow();
                rs1.beforeFirst();
            }

            res = new Rating[rows];
            int i = 0;

            while(rs1.next())
            {
                int ratingID = rs1.getInt("ratingID");
                int itemID = rs1.getInt("itemID");
                int rating = rs1.getInt("rating");
                String dat = rs1.getString("ratingDate");

                Rating rat = new Rating(ratingID, itemID, rating, dat);
                res[i] = rat;
                ++i;
            }
            rs2 = st.executeUpdate(query2);
            st.close();
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
        return res;
    }
}
