
class Session {

    public:

        Session();

        bool open();
        bool close();

    private:

        int _id;
        int _creation_date;
        int _ingame_date;
        bool _locked;

};