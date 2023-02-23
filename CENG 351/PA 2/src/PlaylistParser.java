import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Scanner;

public class PlaylistParser {
	// Parsing the input file in order to use GUI tables.
	public static ArrayList<CengSong> parseSongsFromFile(String filename) {
		ArrayList<CengSong> songList = new ArrayList<CengSong>();
		Scanner s = null;;
		try {
			s = new Scanner(new File(filename), "UTF-8");
		} catch (FileNotFoundException e1) {
			e1.printStackTrace();
		}

		while ( s.hasNextLine()) {
			String myLine = s.nextLine();
			//System.out.println(myLine);

			String[] array = myLine.split("[|]");
			Integer key = Integer.parseInt(array[1]);
			String genre = array[2];
			String name = array[3];
			String artist = array[4];

			songList.add(new CengSong(key,name,artist,genre));
		}
		s.close();
		return songList;
	}
	
	public static void startParsingCommandLine() throws IOException {
		@SuppressWarnings("resource")
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		boolean running = true;
		String inpLine = null;
		while(running){
			inpLine = reader.readLine();
			String[] array = inpLine.split("[|]");
			String command = array[0];
			if(command.equalsIgnoreCase("add")){
				Integer key = Integer.parseInt(array[1]);
				String genre = array[2];
				String name = array[3];
				String artist = array[4];
				
				CengPlaylist.addSong(new CengSong(key,name,artist,genre));
			}
			else if(command.equalsIgnoreCase("quit")){
				running = false;
			}
			else if(command.equalsIgnoreCase("search")){
				int key = Integer.parseInt(array[1]);
				CengPlaylist.searchSong(key);
			}
			else if(command.equalsIgnoreCase("print1")){
				CengPlaylist.printPrimary();
			}
			else if(command.equalsIgnoreCase("print2")){
				CengPlaylist.printSecondary();
			}
			
		}
		
		// 
		// There are 5 commands:
		// 1) quit : End the application. Print nothing, call nothing, just terminate.
		// 2) add : Parse and create the song, calls CengPlaylist.addSong(newSong)
		// 3) search : Parse the key in primary tree, calls CengPlaylist.searchSong(key)
		// 4) print1 : Print the whole primary tree, calls CengPlaylist.printPrimary()
		// 4) print2 : Print the whole secondary tree, calls CengPlaylist.printSecondary()

		// Commands (quit, add, search1, print1, print2) are case-insensitive.
	}
}