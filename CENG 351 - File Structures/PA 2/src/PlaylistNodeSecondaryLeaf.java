import java.util.ArrayList;

public class PlaylistNodeSecondaryLeaf extends PlaylistNode {
    private ArrayList<ArrayList<CengSong>> songBucket;

    public PlaylistNodeSecondaryLeaf(PlaylistNode parent) {
        super(parent);
        songBucket = new ArrayList<ArrayList<CengSong>>();
        this.type = PlaylistNodeType.Leaf;
    }

    public PlaylistNodeSecondaryLeaf(PlaylistNode parent, ArrayList<ArrayList<CengSong>> songBucket ) {
        super(parent);
        this.songBucket = songBucket;
        this.type = PlaylistNodeType.Leaf;
    }

    public void addSong(int index, CengSong song) {
        if(songBucket.size() <= index) {
            songBucket.add(new ArrayList<>());
        }
        else if(!song.genre().equalsIgnoreCase(this.genreAtIndex(index))){
            songBucket.add(index, new ArrayList<>());

        }
        songBucket.get(index).add(song);

    }


    // GUI Methods - Do not modify
    public int genreCount() {
        return songBucket.size();
    }

    public String genreAtIndex(Integer index) {
        if(index >= this.genreCount()) {
            return null;
        }
        else {
            CengSong song = this.songBucket.get(index).get(0);

            return song.genre();
        }
    }

    public ArrayList<CengSong> songsAtIndex(Integer index) {
        if(index >= this.genreCount()) {
            return null;
        }
        else if (songBucket.get(index).size() == 0) {
            return null;
        }
        else {
            return this.songBucket.get(index);
        }
    }

    public ArrayList<ArrayList<CengSong>> getSongBucket(){
        return songBucket;
    }


}
