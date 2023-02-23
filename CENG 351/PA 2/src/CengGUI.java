import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JTable;
import javax.swing.ListSelectionModel;
import javax.swing.SwingUtilities;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.JScrollPane;

import java.awt.Color;
import java.awt.Component;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Random;

public class CengGUI 
{	
	private JFrame frame;
	
	private JTable currentSongTable;
	private JTable alreadyAddedSongTable;
	
	private static final Object[] columnNames = new Object[]{"AudioId", "Genre", "Song Name", "Artist"};

	private ArrayList<CengSong> currentSongs;
	private ArrayList<CengSong> addedSongs;
		
	private JPanel mainModel;
	private JPanel secondModel;
		
	private ArrayList<GUILevel> paintedLevels;
	
	public static Integer orderN; // orderN = 2 * order + 1
	
	@SuppressWarnings("serial")
	static ArrayList<Color> definedColors = new ArrayList<Color>(){{
		
		// Pre-defined colors
		add(Color.black);
		//add(Color.white); Color of empty padding
		add(Color.red);
		//add(Color.green); Color of leaf background
		add(Color.blue);
		add(Color.cyan);
		add(Color.gray);
		//add(Color.lightGray); Color of internal background
		add(Color.magenta);
		add(Color.orange);
		add(Color.pink);
		add(Color.yellow);
		
		// Common colors
		add(new Color(128, 0, 0)); // Maroon
		add(new Color(0, 128, 0)); // Olive
		add(new Color(0, 0, 128)); // Navy
		add(new Color(0, 128, 128)); // Teal
		
		// Uncommon colors
		
		add(new Color(240,230,140)); // Khaki
		add(new Color(0,100,0)); // Dark green
		add(new Color(255,140,0)); // Dark orange
		add(new Color(47,79,79)); // Dark slate gray
		add(new Color(0,206,209)); // Dark turquoise
		add(new Color(188,143,143)); // Rosy brown
	}};

	public CengGUI(Integer options)
	{
		initialize(options);		
	}

	public void show()
	{
		frame.setVisible(true);
	}
	
	public void modelNeedsUpdate(Integer options, PlaylistNode root1, PlaylistNode root2) {
		//System.out.println("Updating model...");
		
		if(options%2==1) updateMainModel(root1);
		if(options>1) updateSecondModel(root2);
	}
	
	private void initialize(Integer options) {
		currentSongs = new ArrayList<CengSong>();
		addedSongs = new ArrayList<CengSong>();
		
		frame = new JFrame();
		frame.setSize(512, 384);
		frame.setLocationRelativeTo(null);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(new BoxLayout(frame.getContentPane(), BoxLayout.Y_AXIS));

		if(options%2==1) addMainModel();
		if(options>1) addSecondModel();
		addCurrentTable(options);
		
		addAlreadyAddedTable();
		
        frame.pack();
	}

	private void addMainModel() {
		mainModel = new JPanel();
		mainModel.setLayout(new BoxLayout(mainModel, BoxLayout.Y_AXIS));
		
		frame.getContentPane().add(mainModel);		
	}
	
	private void addSecondModel() {
		secondModel = new JPanel();
		secondModel.setLayout(new BoxLayout(secondModel, BoxLayout.Y_AXIS));
		
		frame.getContentPane().add(secondModel);		
	}
	
	private void updateMainModel(PlaylistNode root) {
		mainModel.removeAll();
		
		Queue<PlaylistNode> queue = new LinkedList<PlaylistNode>();
		
		queue.add(root);
		
		ArrayList<PlaylistNode> allLevels = new ArrayList<PlaylistNode>();
		
		root.level = 1;
		
		Integer maxLevel = root.level;
		
		while(queue.size() > 0) {
			PlaylistNode currentNode = queue.poll();
			
			if(currentNode.getType() == PlaylistNodeType.Internal) {
				PlaylistNodePrimaryIndex castNode = (PlaylistNodePrimaryIndex)currentNode;
				
				ArrayList<PlaylistNode> allChildren = castNode.getAllChildren();
				
				for(PlaylistNode node : allChildren) {
					node.level = currentNode.level + 1;
					maxLevel = node.level;
					queue.add(node);
				}
			}

			allLevels.add(currentNode);
		}
		
		if(paintedLevels != null) {
			paintedLevels.clear();
			paintedLevels = null;
		}
		
		paintedLevels = new ArrayList<GUILevel>();
		
		for(int i = 0; i < maxLevel; i++) {
			GUILevel newLevel = new GUILevel();
			
						
			for(PlaylistNode node : allLevels)
			{
				if(node.level == i + 1) // Level starts with 1
				{						
					newLevel.addNode(node);
				}
			}
			
			mainModel.add(newLevel);
			paintedLevels.add(newLevel);
		}
		
		mainModel.revalidate();
		mainModel.repaint();
		
		frame.revalidate();
		frame.repaint();
		
		if(CengPlaylist.shouldPack()) {
			frame.pack();
		}
	}
	
	private void updateSecondModel(PlaylistNode root) {
		secondModel.removeAll();
		
		Queue<PlaylistNode> queue = new LinkedList<PlaylistNode>();
		
		queue.add(root);
		
		ArrayList<PlaylistNode> allLevels = new ArrayList<PlaylistNode>();
		
		root.level = 1;
		
		Integer maxLevel = root.level;
		
		while(queue.size() > 0) {
			PlaylistNode currentNode = queue.poll();
			
			if(currentNode.getType() == PlaylistNodeType.Internal) {
				PlaylistNodeSecondaryIndex castNode = (PlaylistNodeSecondaryIndex)currentNode;
				
				ArrayList<PlaylistNode> allChildren = castNode.getAllChildren();
				
				for(PlaylistNode node : allChildren) {
					node.level = currentNode.level + 1;
					maxLevel = node.level;
					queue.add(node);
				}
			}

			allLevels.add(currentNode);
		}
		
		if(paintedLevels != null) {
			paintedLevels.clear();
			paintedLevels = null;
		}
		
		paintedLevels = new ArrayList<GUILevel>();
		
		for(int i = 0; i < maxLevel; i++) {
			GUILevel newLevel = new GUILevel();
			
						
			for(PlaylistNode node : allLevels) {
				if(node.level == i + 1) // Level starts with 1
				{
					newLevel.addNode2(node);
				}
			}
			
			secondModel.add(newLevel);
			paintedLevels.add(newLevel);
		}
		
		secondModel.revalidate();
		secondModel.repaint();
		
		frame.revalidate();
		frame.repaint();
		
		if(CengPlaylist.shouldPack()) {
			frame.pack();
		}
	}
	
	private void addCurrentTable(Integer options) {
		JPanel tablePanel = new JPanel();
		tablePanel.setLayout(new BoxLayout(tablePanel, BoxLayout.Y_AXIS));
				
		DefaultTableModel currentSongTableModel = new DefaultTableModel(columnNames, 0);

		ArrayList<CengSong> inputSongs = PlaylistParser.parseSongsFromFile(CengPlaylist.getFilenameToParse());
		
		for(CengSong song : inputSongs) {
			currentSongTableModel.addRow(new Object[]{song.audioId(), song.genre(), song.songName(), song.artist()});
		}
		
		if(currentSongs.size() == 0) {
			currentSongs.addAll(inputSongs);
		}
		
		currentSongTable = new JTable(currentSongTableModel) {
			// Anon class
			private static final long serialVersionUID = 1L;

			public boolean isCellEditable(int row, int column) 
	        {
                return false;               	
	        };
		};
		
		modifyTable(currentSongTable);
		
        final JButton addButton = new JButton("Add Selected Song");
        
        addButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) 
			{
				addSelectedSong();
			}
        });
        
        addButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        
        final JButton print1Button = new JButton("Print Primary Tree");
        
        print1Button.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) 
			{
				System.out.println("print1"); // Only for visual purposes
				CengPlaylist.printPrimary();
			}
        });
        
        print1Button.setAlignmentX(Component.CENTER_ALIGNMENT);
        
        final JButton print2Button = new JButton("Print Secondary Tree");
        
        print2Button.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) 
			{
				System.out.println("print2"); // Only for visual purposes
				CengPlaylist.printSecondary();
			}
        });
        
        print2Button.setAlignmentX(Component.CENTER_ALIGNMENT);
        
        if(options%2==1) tablePanel.add(print1Button);
        if(options>1) tablePanel.add(print2Button);
        tablePanel.add(addButton);
        tablePanel.add(currentSongTable.getTableHeader());
		tablePanel.add(currentSongTable);
	
		JScrollPane scrollPaneCurrentSongs = new JScrollPane(tablePanel);
		
		// Change width manually
        // scrollPaneCurrentSongs.getViewport().setPreferredSize(new Dimension(400, scrollPaneCurrentSongs.getViewport().getPreferredSize().height));

		frame.getContentPane().add(scrollPaneCurrentSongs);
	}
	
	void addAlreadyAddedTable() {
		JPanel tablePanel = new JPanel();
		tablePanel.setLayout(new BoxLayout(tablePanel, BoxLayout.Y_AXIS));
		
		DefaultTableModel addedSongTableModel = new DefaultTableModel(columnNames, 0);
		
		alreadyAddedSongTable = new JTable(addedSongTableModel) {
			// Anon class
			private static final long serialVersionUID = 1L;

			public boolean isCellEditable(int row, int column) 
	        {
                return false;               	
	        };
		};
		
		modifyTable(alreadyAddedSongTable);

		final JButton searchButton = new JButton("Search Selected Song");
        
        searchButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) 
			{
				searchSelectedSong();
			}
        });
        
        searchButton.setAlignmentX(Container.CENTER_ALIGNMENT);
        tablePanel.add(searchButton);
        tablePanel.add(alreadyAddedSongTable.getTableHeader());
		tablePanel.add(alreadyAddedSongTable);
		
		JScrollPane scrollPaneAddedSongs = new JScrollPane(tablePanel);
		
		frame.getContentPane().add(scrollPaneAddedSongs);
	}
	
	private void addSelectedSong() {
		if(currentSongTable.getSelectedRow() == -1) {
			return;
		}
		
		CengSong selectedSong = getSelectedSongFromTable(currentSongTable);
		
		System.out.println("add|" + selectedSong.fullName()); // Only for visual purposes
		
		CengPlaylist.addSong(selectedSong);
				
		currentSongs.remove(selectedSong);
		
		addSongToTable(selectedSong, alreadyAddedSongTable);
		
		addedSongs.add(selectedSong);
		
		removeSelectionFromTable(currentSongTable);
	}

	private void searchSelectedSong() {
		if(alreadyAddedSongTable.getSelectedRow() == -1) {
			return;
		}
		
		CengSong selectedSong = getSelectedSongFromTable(alreadyAddedSongTable);
		
		System.out.println("search|" + selectedSong.audioId()); // Only for visual purposes
		
		CengPlaylist.searchSong(selectedSong.audioId());
	}
	
	// Helpers
	
	private void removeSelectionFromTable(JTable table) {
		Integer selectedRowIndex = table.getSelectedRow();

		DefaultTableModel tableModel = (DefaultTableModel) table.getModel();
		tableModel.removeRow(selectedRowIndex);		
	}
	
	private CengSong getSelectedSongFromTable(JTable table) {
		Integer selectedRowIndex = table.getSelectedRow();
		
		if(table.equals(currentSongTable)) {
			return currentSongs.get(selectedRowIndex);
		}
		else {
			return addedSongs.get(selectedRowIndex);
		}
	}
	
	private void addSongToTable(CengSong song, JTable table) {
		DefaultTableModel tableModel = (DefaultTableModel) table.getModel();
		tableModel.addRow(new Object[]{song.audioId(), song.songName(), song.artist(), song.genre()});
	}
	
	private void modifyTable(final JTable table) {
		table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		
		final DefaultTableModel tableModel = (DefaultTableModel) table.getModel();

    	if(tableModel.getRowCount() != 0) {
    		// Initialize table with first row selected.
        	table.addRowSelectionInterval(0, 0);
    	}
    	
		tableModel.addTableModelListener(new TableModelListener() {      
		    @Override
		    public void tableChanged(TableModelEvent e) 
		    {
		        SwingUtilities.invokeLater(new Runnable() 
		        {
		            @Override
		            public void run()
		            {
		            	if(tableModel.getRowCount() != 0)
		            	{
			            	table.addRowSelectionInterval(0, 0);
		            	}
		            }
		        });
		    }
		});
	}
	
	public static Color getRandomBorderColor() {
		Random rand = new Random();

		if(CengGUI.definedColors.size() > 0) {
			int randomIndex = rand.nextInt(CengGUI.definedColors.size());
			
			Color pickedColor = CengGUI.definedColors.get(randomIndex);
			
			CengGUI.definedColors.remove(pickedColor);
			
			return pickedColor;
		}
		else {
			// Will produce only bright / light colors
			float r = rand.nextFloat() / 2f;
			float g = rand.nextFloat() / 2f;
			float b = rand.nextFloat() / 2f;
			
			return new Color(r, g, b).brighter();
		}
	}
}
