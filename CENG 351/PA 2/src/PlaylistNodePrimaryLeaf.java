import java.util.ArrayList;

public class PlaylistNodePrimaryLeaf extends PlaylistNode {
	private ArrayList<CengSong> songs;
	
	public PlaylistNodePrimaryLeaf(PlaylistNode parent) {
		super(parent);
		songs = new ArrayList<CengSong>();
		this.type = PlaylistNodeType.Leaf;
	}
	
	public PlaylistNodePrimaryLeaf(PlaylistNode parent, ArrayList<CengSong> songs ) {
		super(parent);
		this.songs = songs;
		this.type = PlaylistNodeType.Leaf;
	}
	
	public void addSong(int index, CengSong song) {
		
		songs.add(index, song);
	}
	
	
	// GUI Methods - Do not modify
	public int songCount()
	{
		return songs.size();
	}
	public Integer audioIdAtIndex(Integer index) {
		if(index >= this.songCount()) {
			return -1;
		}
		else {
			CengSong song = this.songs.get(index);
			return song.audioId();
		}
	}
	
	public String songGenreAtIndex(Integer index) {
		if(index >= this.songCount()) {
			return null;
		}
		else {
			CengSong song = this.songs.get(index);
			
			return song.genre();
		}
	}
	
	public CengSong songAtIndex(Integer index) {
		if(index >= this.songCount()) {
			return null;
		}
		else {
			return this.songs.get(index);
		}
	}
	
	public ArrayList<CengSong> getSongs()
	{
		return songs;
	}
	
	
}
