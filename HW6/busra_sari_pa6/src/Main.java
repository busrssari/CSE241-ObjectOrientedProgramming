import Media.*;
import Observer.*;

/**
 * The Main class is the entry point of the application. It creates a dataset and 
 * various media objects, registers observers, and demonstrates adding, removing,
 * and listing media objects as well as the next and previous functionality.
 */
public class Main {
    /**
     * The main method initializes the dataset and observers, adds media objects,
     * performs various operations, and demonstrates the functionality of the 
     * dataset and observers.
     * 
     * @param args Command line arguments (not used in this application).
     */
    public static void main(String[] args) {
        // This is our dataset. We have only one dataset.
        Dataset ds = new Dataset();

        // Let's create different observers.
        Player p1 = new Player();
        Player p2 = new Player();
        Viewer v1 = new Viewer();
        Viewer v2 = new Viewer();

        // Register the observers with the dataset
        ds.register(p1);
        ds.register(p2);
        ds.register(v1);
        ds.register(v2);

        // Here we create different media objects and add them to the dataset
        ds.add(new Image("imagename1", "dimension info1", "other info1"));
        ds.add(new Image("imagename2", "dimension info2", "other info2"));
        ds.add(new Image("imagename3", "dimension info3", "other info3"));
        ds.add(new Image("imagename4", "dimension info4", "other info4"));
        ds.add(new Image("imagename5", "dimension info5", "other info5"));

        ds.add(new Audio("audioname1", "duration1", "other info1"));
        ds.add(new Audio("audioname2", "duration2", "other info2"));
        ds.add(new Audio("audioname3", "duration3", "other info3"));

        ds.add(new Video("videoname1", "duration1", "other info1"));
        ds.add(new Video("videoname2", "duration2", "other info2"));
        ds.add(new Video("videoname3", "duration3", "other info3"));

        ds.add(new Text("textname1", "other info1"));
        ds.add(new Text("textname2", "other info2"));
        ds.add(new Text("textname3", "other info3"));

        // Print the list of media in the dataset
        System.out.println("\nList of Media in the Dataset:");
        ds.showMediaList();

        // Let's use one of the player objects to get the currently playing object
        Playable po = p1.currently_playing();
        if (po != null) {
            // This prints info about the playing object
            po.info();
            // We can remove this object from the dataset
            ds.remove(po);
            // po is no longer in the dataset. All of the interested observers will get this update.
        }

        // Similarly, for the viewer object, get the currently viewed object
        Non_playable np = v1.currently_viewing();
        if (np != null) {
            // This prints info about the object being viewed
            np.info();
        }

        // Show the list of items being viewed by v1
        v1.show_list();

        // Remove an item from the dataset by its name
        ds.remove("imagename1");

        // Show the updated list of media in the dataset
        System.out.println("\nUpdated List of Media in the Dataset:");
        ds.showMediaList();

        // Show the list of registered observers
        ds.showObserverList();

        // Show the playlist for p1
        p1.show_list();

        // Test the next and previous functionality
        System.out.println("\nTesting next and previous functionality:");
        System.out.println("Playing next audio:");
        p1.next("audio");
        System.out.println("Playing previous video:");
        p1.previous("video");

        // Remove observers from the dataset
        ds.remove_observer(p1);
        ds.remove_observer(p2);
        ds.remove_observer(v1);
        ds.remove_observer(v2);

        // Show the updated list of observers
        ds.showObserverList();
    }
}
