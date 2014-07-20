#ifndef __CLAZZY_LANGUAGE_H__
#define __CLAZZY_LANGUAGE_H__

#include "class_def.h"
#include <vector>
#include <string>
#include <map>
#include <mutex>
#include <ostream>

namespace clazzy {
    class language {
        public:
            language(std::mutex*, bool debug = false);
            virtual ~language() {}

            virtual std::string get_name() const = 0;
            virtual void create(
                                const std::vector<class_def>&,
                                const std::map<std::string,std::string>&
                    ) const = 0;

            static const char TWO_SPACES[];
            static const char FOUR_SPACES[];
            static const char EIGHT_SPACES[];

        protected:
            // helper functions for all langauges
            void debug(const std::string &) const;
            void warn(const std::string &) const;
            void error(const std::string &) const;

        private:
            std::mutex *_io_mutex;
            bool _debug_enabled;
    };
}

#endif
