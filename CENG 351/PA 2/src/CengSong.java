public class CengSong {
	private Integer audioId;
	
	private String songName;
	private String artist;
	private String genre;
	
	public CengSong(Integer audioId, String songName, String artist, String genre) {
		this.audioId = audioId;
		this.songName = songName;
		this.artist = artist;
		this.genre = genre;
	}
	
	// Getters
	
	public Integer audioId()
	{
		return audioId;
	}
	public String songName()
	{
		return songName;
	}
	public String artist()
	{
		return artist;
	}
	public String genre()
	{
		return genre;
	}
	
	// GUI method - do not modify
	public String fullName()
	{
		return "" + audioId() + "|" + genre() + "|" + songName() + "|" + artist();
	}
	
	// DO NOT ADD SETTERS
}
