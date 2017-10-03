class Engine {
public:
  void Update (float dt);
  void MainLoop ();

  void AddListener(std::string event, std::string id, Component* component);
  void RemoveListener(std::string event, std::string id);

  void ExecuteEvent(std::string event);
 
private:
};