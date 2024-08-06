#ifndef _filesystem_hpp_
#define _filesystem_hpp_

#include <filesystem>
#include <string>
#include <variant>
#include <vector>

namespace codecrafter_api
{
  class filesystem
  {
  private:
    class content_node
    {
    public:
      using content_node_variant_type = std::variant<std::string, content_node *>;
    private:
      std::string name_;
      std::vector<content_node_variant_type> contents_;

    public:
      content_node( std::string new_name_, const content_node_variant_type & new_content = nullptr );
      content_node( std::string new_name_, const std::vector<content_node *> & new_contents );
      content_node( const content_node & new_node );
      content_node( content_node && new_node );
      ~content_node();

    private:
      content_node * find( const std::string & find_name );

    public:
      const std::vector<content_node_variant_type> & get_content();
      std::vector<std::string> get_string_content();
      const std::vector<content_node_variant_type> operator[]( const std::string & key );
      content_node_variant_type operator[]( int key );
      const std::vector<std::string> find_content( const std::string & find_name );
      std::string get_name();
    };

  private:
    std::filesystem::path path_;
    content_node *content_;
  public:
    std::string rought_path_name_ = "";

    content_node * req_search( const std::filesystem::path &entity );

  public:
    filesystem();
    filesystem(const std::string & path_name);
    filesystem(const filesystem & new_fs);
    filesystem & operator=(const filesystem & new_fs);
    filesystem(filesystem && new_fs);
    filesystem & operator=(filesystem && new_fs);
    ~filesystem();

  public:
    void add_content( const std::string new_std_content );
    void reset_content( const std::string new_std_content );
    std::string get_content() const;
    std::vector<content_node *> get_subfiles() const;
    std::string get_filename() const;
  public:
    void create_dir();
    std::string create_file();
  private:
    void create_dir(std::filesystem::path new_path);
  };
};

#endif // _filesystem_hpp_