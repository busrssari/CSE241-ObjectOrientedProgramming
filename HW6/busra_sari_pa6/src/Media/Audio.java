package Media;

/**
 * Represents an audio media item that is playable and non-visual.
 */
public class Audio implements Non_visual, Playable {
    private String name;
    private String duration;
    private String info;

    /**
     * Constructs an Audio object with the specified name, duration, and additional information.
     *
     * @param name     the name of the audio
     * @param duration the duration of the audio
     * @param info     additional information about the audio
     */
    public Audio(String name, String duration, String info) {
        this.name = name;
        this.duration = duration;
        this.info = info;
    }

    /**
     * Plays the audio.
     */
    @Override
    public void play() {
        System.out.println("Playing audio: " + name);
    }

    /**
     * Displays information about the audio.
     */
    @Override
    public void info() {
        System.out.println("Audio: " + name + ", Duration: " + duration + ", Info: " + info);
    }

    /**
     * Retrieves the name of the audio.
     *
     * @return the name of the audio
     */
    @Override
    public String getName() {
        return name;
    }
}

