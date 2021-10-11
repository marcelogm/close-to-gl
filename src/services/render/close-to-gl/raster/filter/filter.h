#include "../../../../../services/services.hpp"
#include <stb_image_write.h>
#include <format>

using data::Texture;

#define MIPMAP_LEVEL_COUNT 9

namespace filter {

	class FilterStrategy {
	protected:
		Config* config;
	public:
		virtual bool matches() = 0;
		virtual vec3 apply(Texture*, float, float, vec3, float, float) = 0;
	};

	class NoTexture: public FilterStrategy {
	public:
		NoTexture();
		vec3 apply(Texture* texture, float x, float y, vec3 color, float deltaX, float deltaY);
		bool matches();
	};

	class NearestNeighborResampling : public FilterStrategy {
	public:
		NearestNeighborResampling();
		vec3 apply(Texture* texture, float x, float y, vec3 color, float deltaX, float deltaY);
		bool matches();
	}; 
	
	class BilinearResampling : public FilterStrategy {
	public:
		BilinearResampling();
		vec3 apply(Texture* texture, float x, float y, vec3 color, float deltaX, float deltaY);
		bool matches();
	private:
		vec3 getTexturePixel(Texture* texture, int x, int y);
	};


	class TextureMipmap {
	private:
		vector<Texture*> pyramid;
	public:
		TextureMipmap(size_t levels);
		Texture* getLevel(size_t level);
		void setLevel(size_t level, Texture* texture);
	};

	class MipmapPyramidProvider {
	private:
		static MipmapPyramidProvider* instance;
		MipmapPyramidProvider() = default;
		TextureMipmap* mipmap;
		Texture* getNextLevel(Texture* texture);
		BYTE getTexelAverage(Texture* texture, int x, int y, int offset);
	public:
		static MipmapPyramidProvider* getInstance();
		Texture* get(size_t level);
		void create(Texture* texture);
	};

	class MipmapResampling : public FilterStrategy {
	private:
		MipmapPyramidProvider* mipmapProvider;
		BilinearResampling* bilinear;
		float getMipmapLevel(float deltaX, float deltaY, int width, int height);
	public:
		MipmapResampling();
		vec3 apply(Texture* texture, float x, float y, vec3 color, float deltaX, float deltaY);
		bool matches();
	};

};