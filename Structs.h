#ifndef STRUCTS_H
#define STRUCTS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

namespace structs
{
	struct uvPosTranslated
	{
		public:
			glm::vec2 ll,ul,lr,ur;
			uvPosTranslated()
			{
				ll=glm::vec2(0,0);
				ul=glm::vec2(0,0);
				lr=glm::vec2(0,0);
				ur=glm::vec2(0,0);
			}
			
	};
}
#endif