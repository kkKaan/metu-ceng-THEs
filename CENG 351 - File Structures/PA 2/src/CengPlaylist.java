import java.awt.EventQueue;

public class CengPlaylist {
	
	private static Integer order;
	
	private static String fileName;
	private static Integer guiOptions;
	
	private static Boolean guiEnabled;
	
	private static PlaylistTree playlistTree;
	private static CengGUI window;

	
	private static Boolean wrapNodes = true;
	private static Boolean packFrame = false;
	
	public static void main(String[] args) throws Exception {
			
		if(args.length <2) {
			throw new Exception("Usage : java CengPlaylist -order- -guiOptions- (-guiFileName-) ");
		}		
		
		order = Integer.parseInt(args[0]);
		guiOptions = Integer.parseInt(args[1]);
		
		if(args.length == 2 && guiOptions!=0) {
			throw new Exception("In order to use GUI, provide an input file");			
		}
		
		if(guiOptions>0 && guiOptions<4) {
			guiEnabled=true;
			fileName = args[2];
		}
		else if (guiOptions==0) guiEnabled=false;
		else {
			throw new Exception("Invalid GUI Options Value");			
		}		
		
		playlistTree = new PlaylistTree(order);
				
		Integer orderN = 2 * order + 1; // N-based order, for GUI purposes only.

		CengGUI.orderN = orderN;
		
		if(guiEnabled) {
			EventQueue.invokeLater(new Runnable() {
				public void run() {
					try {
						window = new CengGUI(guiOptions);
						window.show();
					} 
					catch (Exception e) {
						e.printStackTrace();
					}
				}
			});
		}
		
		PlaylistParser.startParsingCommandLine();
	}
	
	public static void addSong (CengSong song) {
		playlistTree.addSong (song);
		
		if(guiEnabled) {
			if(window == null) {
				System.out.println("Err: Window is not initialized yet.");
				return;
			}
			window.modelNeedsUpdate(guiOptions, playlistTree.primaryRoot, playlistTree.secondaryRoot);
		}
	}

	public static void searchSong(Integer key) {
		playlistTree.searchSong(key);
	}
	
	public static void printPrimary() {
		playlistTree.printPrimaryPlaylist();
		
		if(guiEnabled) {
			window.modelNeedsUpdate(guiOptions, playlistTree.primaryRoot, playlistTree.secondaryRoot);
		}
	}
	
	public static void printSecondary() {
		playlistTree.printSecondaryPlaylist();
		
		if(guiEnabled) {
			window.modelNeedsUpdate(guiOptions, playlistTree.primaryRoot, playlistTree.secondaryRoot);
		}
	}
	
	public static void setPrimaryRoot(PlaylistNode newRoot) {
		playlistTree.primaryRoot=newRoot;
	}
	
	public static void setSecondaryRoot(PlaylistNode newRoot) {
		playlistTree.secondaryRoot=newRoot;
	}
	
	public static String getFilenameToParse()
	{
		return CengPlaylist.fileName;
	}
	
	public static Boolean shouldWrap()
	{
		return CengPlaylist.wrapNodes;
	}
	
	public static Boolean shouldPack()
	{
		return CengPlaylist.packFrame;
	}
}

	

