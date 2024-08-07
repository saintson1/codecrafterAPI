#include "filesystem.hpp"

#include <filesystem>
#include <fstream>
#include <string>
#include <exception>
#include <variant>
#include <ios>

namespace codecrafter_api
{
  filesystem::content_node::content_node( std::string new_name_, const content_node_variant_type & new_content)
          : name_(std::move(new_name_))
  {
    contents_.push_back(new_content);
  };

  filesystem::content_node::content_node( std::string new_name_, const std::vector<content_node *> & new_contents )
          : name_(std::move(new_name_))
  {
    for (const auto & content : new_contents)
      contents_.emplace_back(content);
  };

  filesystem::content_node::content_node( const content_node & new_node ) : name_(new_node.name_)
  {
    for (auto & content : new_node.contents_)
      if (std::get_if<content_node *>(&content))
        contents_.emplace_back(new content_node(*std::get<content_node *>(content)));
      else
        contents_.emplace_back(std::get<std::string>(content));
  };

  filesystem::content_node::content_node( content_node && new_node ) : name_(std::move(new_node.name_))
  {
    for (auto & content : new_node.contents_)
      if (std::get_if<content_node *>(&content))
      {
        contents_.emplace_back(std::get<content_node *>(content));
      }
      else
        contents_.emplace_back(std::move(std::get<std::string>(content)));

        new_node.contents_ = std::vector{content_node_variant_type("")};
  };

  filesystem::content_node::~content_node()
  {
    for (auto content : contents_)
    {
      content_node ** dell_dbl_ptr = std::get_if<content_node *>(&content);
      if (dell_dbl_ptr)
        delete *dell_dbl_ptr;
    }
  };

  filesystem::content_node * filesystem::content_node::find( const std::string & find_name )
  {
    if (name_ == find_name)
      return this;

    for (auto & node : contents_)
      if (std::get_if<content_node *>(&node))
      {
        content_node *ans = std::get<content_node *>(node)->find(find_name);
        if (ans)
          return ans;
      }

    return nullptr;
  };

  const std::vector<filesystem::content_node::content_node_variant_type> & filesystem::content_node::get_content() { return contents_; };

  std::vector<std::string> filesystem::content_node::get_string_content()
  {
    std::vector<std::string> string_content;

    for (auto & node : contents_)
      if (std::get_if<std::string>(&node))
        string_content.push_back(std::get<std::string>(node));
    return string_content;
  };

  const std::vector<filesystem::content_node::content_node_variant_type> filesystem::content_node::operator[]( const std::string & key )
  {
    content_node *node = find(key);
    if (node)
      return node->contents_;

    return std::vector<content_node_variant_type>();
  };

  filesystem::content_node::content_node_variant_type filesystem::content_node::operator[]( int key )
  {
    if (contents_.size() > key)
      return contents_[key];
    return nullptr;
  };

  const std::vector<std::string> filesystem::content_node::find_content( const std::string & find_name )
  {
    std::vector<std::string> ans;

    content_node *node = find(find_name);
    if (node)
      for (auto & content : node->contents_)
        if (std::get_if<std::string>(&content))
          ans.push_back(std::get<std::string>(content));
    return ans;
  };

  std::string filesystem::content_node::get_name() { return name_; };

  void filesystem::content_node::add_string_content( const std::string & new_string_content )
  {
    if (get_string_content().empty())
      return;

    for (auto & content : contents_)
      if (std::get_if<std::string>(&content))
        *std::get_if<std::string>(&content) += new_string_content;

    return;
  };


  filesystem::content_node * filesystem::req_search (const std::filesystem::path &entity)
  {
    try
    {
      if (std::filesystem::exists(entity))
      {
        if (std::filesystem::is_regular_file(entity))
        {
          std::ifstream fs(entity.generic_string());
          std::string content;
          if (!fs.is_open())
            throw std::runtime_error("file not open");

          std::string buf_line;
          while (std::getline(fs, buf_line))
            content += buf_line;
          fs.close();

          return new content_node(entity.filename().generic_string(), content);
        }
        else if (std::filesystem::is_directory(entity))
        {
          std::vector<content_node *> buf_vector;
          for (auto &unit : std::filesystem::directory_iterator(entity))
          {
            buf_vector.push_back(req_search(unit.path()));
          }
          return new content_node(entity.filename().generic_string(), buf_vector);
        }
        else
          return nullptr;
      }
      else
        return nullptr;

    }
    catch (const std::filesystem::filesystem_error &ex)
    {
      throw std::runtime_error(ex.what());
    }
    catch (const std::runtime_error &err_ex)
    {
      throw err_ex;
    }
  };

  filesystem::filesystem() : content_(nullptr) {  };

  filesystem::filesystem(const std::string & path_name) : path_(std::filesystem::path(path_name)), content_(req_search(path_)), rought_path_name_(path_name) {  };

  filesystem::filesystem(const filesystem & new_fs) : path_(new_fs.path_), content_(new content_node(*new_fs.content_)), rought_path_name_(new_fs.rought_path_name_) {  };

  filesystem & filesystem::operator=(const filesystem & new_fs)
  {
    path_ = new_fs.path_;
    content_ = new content_node(*new_fs.content_);
    rought_path_name_ = new_fs.rought_path_name_;

    return *this;
  };

  filesystem::filesystem(filesystem && new_fs) : path_(std::move(new_fs.path_)), content_(new content_node(std::move(*new_fs.content_))), rought_path_name_(new_fs.rought_path_name_) { new_fs.content_ = nullptr; };

  filesystem & filesystem::operator=(filesystem && new_fs)
  {
    path_ = std::move(new_fs.path_);
    content_ = new content_node(std::move(*new_fs.content_));
    new_fs.content_ = nullptr;
    rought_path_name_ = new_fs.rought_path_name_;

    return *this;
  };

  filesystem::~filesystem()
  {
    delete content_;
  };

  std::string filesystem::get_content() const
  {
    for (auto & content : content_->get_string_content())
      return content;
    return "";
  };

  std::vector<filesystem::content_node *> filesystem::get_subfiles() const
  {
    std::vector<content_node *> subfiles;

    for (auto & content : content_->get_content())
      if (std::get_if<content_node *>(&content))
        subfiles.emplace_back(std::get<content_node *>(content));
    return subfiles;
  };

  std::string filesystem::get_filename() const
  {
    return path_.filename().generic_string();
  };

  int filesystem::add_content( const std::string & new_str_content )
  {
    if (!std::filesystem::is_regular_file(path_))
      return -1;

    std::fstream fs;
    fs.open(path_.generic_string(), std::ios::out | std::ios::app);
    if (!fs.is_open())
    {
      fs.close();
      throw std::runtime_error("file not open");
    }

    fs << new_str_content;
    fs.close();

    content_->add_string_content(new_str_content);
    return 0;
  };

  int filesystem::reset_content( const std::string & new_str_content )
  {
    if (!std::filesystem::is_regular_file(path_))
      return -1;

    std::fstream fs;
    fs.open(path_.generic_string(), std::ios::out);
    if (!fs.is_open())
    {
      fs.close();
      throw std::runtime_error("file not open");
    }

    fs << new_str_content;
    fs.close();

    delete content_;

    content_ = new content_node(path_.filename().generic_string(), new_str_content);

    return 0;
  };

  void filesystem::create_dir()
  {
    if (content_ || rought_path_name_ == "")
      return;
    try
    {
      std::filesystem::create_directories(path_);
    }
    catch(...)
    {
      throw;
    }
    return;
  };

  void filesystem::create_dir(std::filesystem::path new_path)
  {
    if (new_path.empty())
      return;
    try
    {
      std::filesystem::create_directories(new_path);
    }
    catch(...)
    {
      throw;
    }

    return;
  };

  std::string filesystem::create_file()
  {
    if (content_)
      return get_content();
    try
    {
      if (rought_path_name_ == "")
        throw std::runtime_error("invalid filename");

      filesystem().create_dir(path_.parent_path());

      std::fstream new_file;
      new_file.open(rought_path_name_, std::ios::out);

      if (!new_file.is_open())
        throw std::runtime_error("file w'not created");
      new_file.close();
    }
    catch(...)
    {
      throw;
    }
    return "";
  };
}