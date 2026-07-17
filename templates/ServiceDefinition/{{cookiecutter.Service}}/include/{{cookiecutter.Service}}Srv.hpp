/**
 * @file {{cookiecutter.Service}}Srv.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2026-07-17
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#pragma once
namespace fast::rf::messages::{{cookiecutter.Package}}Msgs {
  struct {{cookiecutter.Service}}Srv {
    {{cookiecutter.Service}}Srv() {
      struct {{cookiecutter.Service}}Request {
        {{cookiecutter.Service}}Request() {}
      } request ;

      struct {{cookiecutter.Service}}Response {
        {{cookiecutter.Service}}Response() {}
      } response ;

      {{cookiecutter.Service}}Srv() {}
    }
  };
} // namespace fast::rf::messages::{{cookiecutter.Package}}
