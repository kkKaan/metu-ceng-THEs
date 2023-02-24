import java.util.ArrayList;

public class PlaylistTree
{

	public PlaylistNode primaryRoot;	//root of the primary B+ tree
	public PlaylistNode secondaryRoot;	//root of the secondary B+ tree
	public PlaylistTree(Integer order)
	{
		PlaylistNode.order = order;
		primaryRoot = new PlaylistNodePrimaryLeaf(null);
		primaryRoot.level = 0;
		secondaryRoot = new PlaylistNodeSecondaryLeaf(null);
		secondaryRoot.level = 0;
	}

	public void addSong(CengSong song)
	{
		// Add song to primary B+ tree in increasing order of audioId
		PlaylistNode currentNode = this.primaryRoot;
		int i = 0;

		while (currentNode.type == PlaylistNodeType.Internal)
		{
			PlaylistNodePrimaryIndex currentIndexNode = (PlaylistNodePrimaryIndex) currentNode;
			for (i = 0; i < currentIndexNode.audioIdCount(); i++)
			{
				if (song.audioId() < currentIndexNode.audioIdAtIndex(i)) break;
			}
			currentNode = currentIndexNode.getChildrenAt(i);
		}

		PlaylistNodePrimaryLeaf currentLeafNode = (PlaylistNodePrimaryLeaf) currentNode;

		for (i = 0; i < currentLeafNode.songCount(); i++)
		{
			if (song.audioId() < currentLeafNode.audioIdAtIndex(i)) break;
		}
		currentLeafNode.addSong(i, song);

		if (currentLeafNode.songCount() > 2 * PlaylistNode.order)
		{
			// Split leaf node and propagate split up to root if necessary
			splitLeafNode(currentLeafNode);
		}

		// Add song to secondary B+ tree in increasing order of genre
		currentNode = this.secondaryRoot;
		i = 0;

		while (currentNode.type == PlaylistNodeType.Internal)
		{
			PlaylistNodeSecondaryIndex currentIndexNode = (PlaylistNodeSecondaryIndex) currentNode;
			for (i = 0; i < currentIndexNode.genreCount(); i++)
			{
				if (song.genre().compareTo(currentIndexNode.genreAtIndex(i)) < 0) break;
			}
			currentNode = currentIndexNode.getChildrenAt(i);
		}

		PlaylistNodeSecondaryLeaf currentLeafNode2 = (PlaylistNodeSecondaryLeaf) currentNode;

		for (i = 0; i < currentLeafNode2.genreCount(); i++)
		{
			if (song.genre().compareTo(currentLeafNode2.genreAtIndex(i)) < 0) break;
		}

		if(i == 0)
		{
			currentLeafNode2.addSong(i, song);
		}
		else if(song.genre().compareTo(currentLeafNode2.genreAtIndex(i-1)) == 0)
		{
			currentLeafNode2.addSong(i-1, song);
		}
		else
		{
			currentLeafNode2.addSong(i, song);
		}

		if (currentLeafNode2.genreCount() > 2 * PlaylistNode.order)
		{
			// Split leaf node and propagate split up to root if necessary
			splitSecLeafNode(currentLeafNode2);
		}
	}

	public CengSong searchSong(Integer audioId)
	{
		// find the song with the searched audioId in primary B+ tree
		// return value will not be tested, just print according to the specifications
		// also print each index in the path

		PlaylistNode currentNode = this.primaryRoot;
		int i, a;
		int indentCount = 0;

		while (currentNode.type == PlaylistNodeType.Internal)
		{
			PlaylistNodePrimaryIndex currentIndexNode = (PlaylistNodePrimaryIndex) currentNode;
			for (a = 0; a < indentCount; a++) System.out.print("\t");
			System.out.println("<index>");

			for (i = 0; i < currentIndexNode.audioIdCount(); i++)
			{
				for (a = 0; a < indentCount; a++) System.out.print("\t");
				System.out.println(currentIndexNode.audioIdAtIndex(i));
			}
			for (i = 0; i < currentIndexNode.audioIdCount(); i++)
			{
				if (audioId < currentIndexNode.audioIdAtIndex(i)) break;
			}
			currentNode = currentIndexNode.getChildrenAt(i);

			for (a = 0; a < indentCount; a++) System.out.print("\t");
			System.out.println("</index>");
			++indentCount;
		}

		PlaylistNodePrimaryLeaf currentLeafNode = (PlaylistNodePrimaryLeaf) currentNode;

		for (i = 0; i < currentLeafNode.songCount(); i++)
		{
			if (audioId == currentLeafNode.audioIdAtIndex(i)) break;
		}

		if (i == currentLeafNode.songCount())
		{
			System.out.println("Could not find " + audioId);
			return null;
		}
		else
		{
			for (a = 0; a < indentCount; a++) System.out.print("\t");
			System.out.println("<data>");

			for (a = 0; a < indentCount; a++) System.out.print("\t");
			System.out.println("<record>" + currentLeafNode.audioIdAtIndex(i) + "|" + currentLeafNode.songAtIndex(i).genre() + "|" + currentLeafNode.songAtIndex(i).songName() + "|" + currentLeafNode.songAtIndex(i).artist() + "</record>");

			for (a = 0; a < indentCount; a++) System.out.print("\t");
			System.out.println("</data>");

			return currentLeafNode.songAtIndex(i);
		}
	}


	public void printPrimaryPlaylist()
	{
		// print the primary B+ tree in Depth-first order
		dfsPrimary(0, this.primaryRoot);
	}

	public void printSecondaryPlaylist()
	{
		// print the secondary B+ tree in Depth-first order
		dfsSecondary(0, this.secondaryRoot);
	}

	// Extra functions if needed

	private void splitLeafNode(PlaylistNodePrimaryLeaf leafNode)
	{
		// Split leaf node and propagate split up to root if necessary
		if (leafNode.getParent() == null)
		{
			// Create new root
			PlaylistNodePrimaryIndex newRoot = new PlaylistNodePrimaryIndex(null);
			newRoot.addAudioId(0, leafNode.audioIdAtIndex(PlaylistNode.order));

			PlaylistNodePrimaryLeaf newLeafLeftNode = new PlaylistNodePrimaryLeaf(newRoot);
			PlaylistNodePrimaryLeaf newLeafRightNode = new PlaylistNodePrimaryLeaf(newRoot);

			int i = 0;
			for (i = 0; i < PlaylistNode.order; i++)
			{
				newLeafLeftNode.addSong(i, leafNode.songAtIndex(i));
			}

			for (; i < leafNode.songCount(); i++) // copy up, keep middle element
			{
				newLeafRightNode.addSong(i - PlaylistNode.order, leafNode.songAtIndex(i));
			}

			newRoot.addChild(0, newLeafLeftNode);
			newRoot.addChild(1, newLeafRightNode);
			primaryRoot = newRoot;
		}
		else
		{
			// Propagate split up to root
			PlaylistNodePrimaryIndex parentNode = (PlaylistNodePrimaryIndex) leafNode.getParent();
			int i = 0;
			for (i = 0; i < parentNode.audioIdCount(); i++)
			{
				if (leafNode.audioIdAtIndex(PlaylistNode.order) < parentNode.audioIdAtIndex(i)) break;
			}

			parentNode.addAudioId(i, leafNode.audioIdAtIndex(PlaylistNode.order));
			PlaylistNodePrimaryLeaf newLeafLeftNode = new PlaylistNodePrimaryLeaf(parentNode);
			PlaylistNodePrimaryLeaf newLeafRightNode = new PlaylistNodePrimaryLeaf(parentNode);

			int j = 0;
			for (j = 0; j < PlaylistNode.order; j++)
			{
				newLeafLeftNode.addSong(j, leafNode.songAtIndex(j));
			}

			for (; j < leafNode.songCount(); j++) // copy up, keep middle element
			{
				newLeafRightNode.addSong(j - PlaylistNode.order, leafNode.songAtIndex(j));
			}

			parentNode.addChild(i, newLeafLeftNode);
			parentNode.addChild(i+1, newLeafRightNode);
			parentNode.removeChild(i+2);

			if (parentNode.audioIdCount() > 2 * PlaylistNode.order)
			{
				// Split index node and propagate split up to root if necessary
				splitIndexNode(parentNode);
			}
		}
	}

	private void splitIndexNode(PlaylistNodePrimaryIndex indexNode)
	{
		// Split index node and propagate split up to root if necessary
		if (indexNode.getParent() == null)
		{
			// Create new root
			PlaylistNodePrimaryIndex newRoot = new PlaylistNodePrimaryIndex(null);
			newRoot.addAudioId(0, indexNode.audioIdAtIndex(PlaylistNode.order));

			PlaylistNodePrimaryIndex newIndexLeftNode = new PlaylistNodePrimaryIndex(newRoot);
			PlaylistNodePrimaryIndex newIndexRightNode = new PlaylistNodePrimaryIndex(newRoot);

			int i = 0;
			for (i = 0; i < PlaylistNode.order; i++)
			{
				newIndexLeftNode.addAudioId(i, indexNode.audioIdAtIndex(i));
				newIndexLeftNode.addChild(i, indexNode.getChildrenAt(i));
				indexNode.getChildrenAt(i).setParent(newIndexLeftNode);
			}
			newIndexLeftNode.addChild(i, indexNode.getChildrenAt(i));
			indexNode.getChildrenAt(i).setParent(newIndexLeftNode);

			++i;
			for (; i < indexNode.audioIdCount(); i++)
			{
				newIndexRightNode.addAudioId(i - PlaylistNode.order - 1, indexNode.audioIdAtIndex(i));
				newIndexRightNode.addChild(i - PlaylistNode.order - 1, indexNode.getChildrenAt(i));
				indexNode.getChildrenAt(i).setParent(newIndexRightNode);
			}
			newIndexRightNode.addChild(i - PlaylistNode.order - 1, indexNode.getChildrenAt(i));
			indexNode.getChildrenAt(i).setParent(newIndexRightNode);

			newRoot.addChild(0, newIndexLeftNode);
			newRoot.addChild(1, newIndexRightNode);
			primaryRoot = newRoot;
		}
		else
		{
			// Propagate split up to root
			PlaylistNodePrimaryIndex parentNode = (PlaylistNodePrimaryIndex) indexNode.getParent();
			int i = 0;
			for (i = 0; i < parentNode.audioIdCount(); i++)
			{
				if (indexNode.audioIdAtIndex(PlaylistNode.order) < parentNode.audioIdAtIndex(i)) break;
			}

			parentNode.addAudioId(i, indexNode.audioIdAtIndex(PlaylistNode.order));
			PlaylistNodePrimaryIndex newIndexLeftNode = new PlaylistNodePrimaryIndex(parentNode);
			PlaylistNodePrimaryIndex newIndexRightNode = new PlaylistNodePrimaryIndex(parentNode);

			int j = 0;
			for (j = 0; j < PlaylistNode.order; j++)
			{
				newIndexLeftNode.addAudioId(j, indexNode.audioIdAtIndex(j));
				newIndexLeftNode.addChild(j, indexNode.getChildrenAt(j));
				indexNode.getChildrenAt(j).setParent(newIndexLeftNode);
			}
			newIndexLeftNode.addChild(j, indexNode.getChildrenAt(j));
			indexNode.getChildrenAt(j).setParent(newIndexLeftNode);

			++j;
			for (; j < indexNode.audioIdCount(); j++)
			{
				newIndexRightNode.addAudioId(j - PlaylistNode.order - 1, indexNode.audioIdAtIndex(j));
				newIndexRightNode.addChild(j - PlaylistNode.order - 1, indexNode.getChildrenAt(j));
				indexNode.getChildrenAt(j).setParent(newIndexRightNode);
			}
			newIndexRightNode.addChild(j - PlaylistNode.order - 1, indexNode.getChildrenAt(j));
			indexNode.getChildrenAt(j).setParent(newIndexRightNode);

			parentNode.addChild(i, newIndexLeftNode);
			parentNode.addChild(i+1, newIndexRightNode);
			parentNode.removeChild(i+2);

			if (parentNode.audioIdCount() > 2 * PlaylistNode.order)
			{
				// Split index node and propagate split up to root if necessary
				splitIndexNode(parentNode);
			}
		}
	}

	private void splitSecLeafNode(PlaylistNodeSecondaryLeaf leafNode)
	{
		// Split leaf node and propagate split up to root if necessary
		if (leafNode.getParent() == null)
		{
			// Create new root
			PlaylistNodeSecondaryIndex newRoot = new PlaylistNodeSecondaryIndex(null);
			newRoot.addGenre(0, leafNode.genreAtIndex(PlaylistNode.order));

			PlaylistNodeSecondaryLeaf newLeafLeftNode = new PlaylistNodeSecondaryLeaf(newRoot);
			PlaylistNodeSecondaryLeaf newLeafRightNode = new PlaylistNodeSecondaryLeaf(newRoot);

			int i;
			for (i = 0; i < PlaylistNode.order; i++)
			{
				ArrayList<CengSong> songs = leafNode.songsAtIndex(i);

				for (CengSong song : songs)
				{
					newLeafLeftNode.addSong(i, song);
				}
			}

			for (; i < leafNode.genreCount(); i++) // copy up, keep middle element
			{
				ArrayList<CengSong> songs = leafNode.songsAtIndex(i);

				for (CengSong song : songs)
				{
					newLeafRightNode.addSong(i - PlaylistNode.order, song);
				}
			}

			newRoot.addChild(0, newLeafLeftNode);
			newRoot.addChild(1, newLeafRightNode);
			secondaryRoot = newRoot;
		}
		else
		{
			// Propagate split up to root
			PlaylistNodeSecondaryIndex parentNode = (PlaylistNodeSecondaryIndex) leafNode.getParent();
			int i;
			for (i = 0; i < parentNode.genreCount(); i++)
			{
				if (leafNode.genreAtIndex(PlaylistNode.order).compareTo(parentNode.genreAtIndex(i)) < 0) break;
			}
			parentNode.addGenre(i, leafNode.genreAtIndex(PlaylistNode.order));

			PlaylistNodeSecondaryLeaf newLeafLeftNode = new PlaylistNodeSecondaryLeaf(parentNode);
			PlaylistNodeSecondaryLeaf newLeafRightNode = new PlaylistNodeSecondaryLeaf(parentNode);

			int j;
			for (j = 0; j < PlaylistNode.order; j++)
			{
				ArrayList<CengSong> songs = leafNode.songsAtIndex(j);

				for (CengSong song : songs)
				{
					newLeafLeftNode.addSong(j, song);
				}
			}

			for (; j < leafNode.genreCount(); j++)
			{
				ArrayList<CengSong> songs = leafNode.songsAtIndex(j);

				for (CengSong song : songs)
				{
					newLeafRightNode.addSong(j - PlaylistNode.order, song);
				}
			}

			parentNode.addChild(i, newLeafLeftNode);
			parentNode.addChild(i+1, newLeafRightNode);
			parentNode.removeChild(i+2);

			if (parentNode.genreCount() > 2 * PlaylistNode.order)
			{
				// Split index node and propagate split up to root if necessary
				splitSecIndexNode(parentNode);
			}
		}
	}

	private void splitSecIndexNode(PlaylistNodeSecondaryIndex indexNode)
	{
		// Split index node and propagate split up to root if necessary
		if (indexNode.getParent() == null)
		{
			// Create new root
			PlaylistNodeSecondaryIndex newRoot = new PlaylistNodeSecondaryIndex(null);
			newRoot.addGenre(0, indexNode.genreAtIndex(PlaylistNode.order));

			PlaylistNodeSecondaryIndex newIndexLeftNode = new PlaylistNodeSecondaryIndex(newRoot);
			PlaylistNodeSecondaryIndex newIndexRightNode = new PlaylistNodeSecondaryIndex(newRoot);

			int i;
			for (i = 0; i < PlaylistNode.order; i++)
			{
				newIndexLeftNode.addGenre(i, indexNode.genreAtIndex(i));
				newIndexLeftNode.addChild(i, indexNode.getChildrenAt(i));
				indexNode.getChildrenAt(i).setParent(newIndexLeftNode);
			}
			newIndexLeftNode.addChild(i, indexNode.getChildrenAt(i));
			indexNode.getChildrenAt(i).setParent(newIndexLeftNode);

			++i;
			for (; i < indexNode.genreCount(); i++)
			{
				newIndexRightNode.addGenre(i - PlaylistNode.order - 1, indexNode.genreAtIndex(i));
				newIndexRightNode.addChild(i - PlaylistNode.order - 1, indexNode.getChildrenAt(i));
				indexNode.getChildrenAt(i).setParent(newIndexRightNode);
			}
			newIndexRightNode.addChild(i - PlaylistNode.order - 1, indexNode.getChildrenAt(i));
			indexNode.getChildrenAt(i).setParent(newIndexRightNode);

			newRoot.addChild(0, newIndexLeftNode);
			newRoot.addChild(1, newIndexRightNode);
			secondaryRoot = newRoot;
		}
		else
		{
			// Propagate split up to root
			PlaylistNodeSecondaryIndex parentNode = (PlaylistNodeSecondaryIndex) indexNode.getParent();
			int i = 0;
			for (i = 0; i < parentNode.genreCount(); i++)
			{
				if (indexNode.genreAtIndex(PlaylistNode.order).compareTo(parentNode.genreAtIndex(i)) < 0) break;
			}

			parentNode.addGenre(i, indexNode.genreAtIndex(PlaylistNode.order));
			PlaylistNodeSecondaryIndex newIndexLeftNode = new PlaylistNodeSecondaryIndex(parentNode);
			PlaylistNodeSecondaryIndex newIndexRightNode = new PlaylistNodeSecondaryIndex(parentNode);

			int j = 0;
			for (j = 0; j < PlaylistNode.order; j++)
			{
				newIndexLeftNode.addGenre(j, indexNode.genreAtIndex(j));
				newIndexLeftNode.addChild(j, indexNode.getChildrenAt(j));
				indexNode.getChildrenAt(j).setParent(newIndexLeftNode);
			}
			newIndexLeftNode.addChild(j, indexNode.getChildrenAt(j));
			indexNode.getChildrenAt(j).setParent(newIndexLeftNode);

			++j;
			for (; j < indexNode.genreCount(); j++)
			{
				newIndexRightNode.addGenre(j - PlaylistNode.order - 1, indexNode.genreAtIndex(j));
				newIndexRightNode.addChild(j - PlaylistNode.order - 1, indexNode.getChildrenAt(j));
				indexNode.getChildrenAt(j).setParent(newIndexRightNode);
			}
			newIndexRightNode.addChild(j - PlaylistNode.order - 1, indexNode.getChildrenAt(j));
			indexNode.getChildrenAt(j).setParent(newIndexRightNode);

			parentNode.addChild(i, newIndexLeftNode);
			parentNode.addChild(i+1, newIndexRightNode);
			parentNode.removeChild(i+2);

			if (parentNode.genreCount() > 2 * PlaylistNode.order)
			{
				// Split index node and propagate split up to root if necessary
				splitSecIndexNode(parentNode);
			}
		}
	}
	private void dfsPrimary(int indent, PlaylistNode root)
	{
		// recursive Depth first search of primary tree
		int i, a;

		if (root instanceof PlaylistNodePrimaryLeaf)
		{
			for (a = 0; a < indent; a++) System.out.print("\t");
			System.out.println("<data>");

			PlaylistNodePrimaryLeaf currentLeafNode = (PlaylistNodePrimaryLeaf) root;
			for (i = 0; i < ((PlaylistNodePrimaryLeaf) root).songCount(); i++)
			{
				for (a = 0; a < indent; a++) System.out.print("\t");
				System.out.println("<record>" + currentLeafNode.audioIdAtIndex(i) + "|" + currentLeafNode.songAtIndex(i).genre() + "|" + currentLeafNode.songAtIndex(i).songName() + "|" + currentLeafNode.songAtIndex(i).artist() + "</record>");
			}
			for (a = 0; a < indent; a++) System.out.print("\t");
			System.out.println("</data>");
		}
		else
		{
			PlaylistNodePrimaryIndex currentIndexNode = (PlaylistNodePrimaryIndex) root;
			for (a = 0; a < indent; a++) System.out.print("\t");
			System.out.println("<index>");

			for (i = 0; i < currentIndexNode.audioIdCount(); i++)
			{
				for (a = 0; a < indent; a++) System.out.print("\t");
				System.out.println(currentIndexNode.audioIdAtIndex(i));
			}
			for(a = 0; a < indent; ++a) System.out.print("\t");
			System.out.println("</index>");

			for (i = 0; i < currentIndexNode.audioIdCount() + 1; i++)
			{
				dfsPrimary(indent + 1, currentIndexNode.getChildrenAt(i));
			}
		}
	}

	private void dfsSecondary(int indent, PlaylistNode root)
	{
		// recursive Depth first search of secondary tree
		int i, j, a;

		if (root instanceof PlaylistNodeSecondaryLeaf)
		{
			for (a = 0; a < indent; a++) System.out.print("\t");
			System.out.println("<data>");

			PlaylistNodeSecondaryLeaf currentLeafNode = (PlaylistNodeSecondaryLeaf) root;
			for (i = 0; i < ((PlaylistNodeSecondaryLeaf) root).genreCount(); i++)
			{
				for (a = 0; a < indent; a++) System.out.print("\t");
				System.out.println(currentLeafNode.genreAtIndex(i));

				ArrayList<CengSong> songs = currentLeafNode.songsAtIndex(i);
				for (j = 0; j < songs.size(); j++)
				{
					for (a = 0; a < indent + 1; a++) System.out.print("\t");
					System.out.println("<record>" + songs.get(j).audioId() + "|" + songs.get(j).genre() + "|" + songs.get(j).songName() + "|" + songs.get(j).artist() + "</record>");
				}
			}
			for (a = 0; a < indent; a++) System.out.print("\t");
			System.out.println("</data>");
		}
		else
		{
			PlaylistNodeSecondaryIndex currentIndexNode = (PlaylistNodeSecondaryIndex) root;
			for (a = 0; a < indent; a++) System.out.print("\t");
			System.out.println("<index>");

			for (i = 0; i < currentIndexNode.genreCount(); i++)
			{
				for (a = 0; a < indent; a++) System.out.print("\t");
				System.out.println(currentIndexNode.genreAtIndex(i));
			}
			for(a = 0; a < indent; ++a) System.out.print("\t");
			System.out.println("</index>");

			for (i = 0; i < currentIndexNode.genreCount() + 1; i++)
			{
				dfsSecondary(indent + 1, currentIndexNode.getChildrenAt(i));
			}
		}
	}
}
