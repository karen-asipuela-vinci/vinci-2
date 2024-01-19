import java.util.ArrayList;
import java.util.List;

public class TodoList {
    private List<String> tasks = new ArrayList<>();
    public boolean add(String task1) {
        return tasks.add(task1);
    }

    public boolean containsTask(String task1) {
        return tasks.contains(task1);
    }
}
